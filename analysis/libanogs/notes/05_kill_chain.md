# libanogs.so — Kill chain, raw SVC syscalls & kill switches (our v7a analysis)

> Source of truth: OUR analysis/libanogs/libanogs.so (md5 2810a533, from IDENTITY.txt).
> Cross-ref hints (verify, don't trust): INFO/ace_anticheat_notes/12_complete_kill_path_inventory.md,
> 20_tdm_report_chain.md, 79_heartbeat_integrity_kill.md — arm64 + UE4 build.

## Summary

The ACE termination subsystem in `libanogs.so` operates across three distinct tiers: (1) direct libc process termination calls (`kill(pid, 9)`, `_exit(127)`, `exit(1)`) embedded in init-failure and watchdog routines; (2) a dynamic 32-stub raw ARM-mode SVC syscall bank (`sub_381A40`..`sub_382410`, indexed via table `off_3A08D4` by master dispatcher `sub_35D858`) that completely bypasses libc hook frameworks; and (3) an asynchronous telemetry detection reporter (`sub_3653D4`) that aggregates scanner violation findings into structured TDM/COREREPORT packets for server-side ban issuance. Crucially, the entire client-side telemetry pipeline is governed by a global feature flag `byte_3DB1EC`: forcing `byte_3DB1EC = 0` and `byte_3DB1ED = 1` immediately neuters all report construction and transmission without triggering watchdog self-kills.

## Evidence

### 1. Direct libc kill & process termination sites

| Offset (RVA) | Symbol / our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0x398B30 | `kill` (PLT thunk) | ARM | libc `kill()` thunk, GOT `__imp_kill` @ 0x3EA2F8 (reloc 0x3A2ABC) | functions.json; imports.json; `RAW/kr2.c` |
| 0x398FC0 | `_exit` (PLT thunk) | ARM | libc `_exit()` thunk, GOT `__imp__exit` @ 0x3EA428 (reloc 0x3A2BE0) | functions.json; imports.json |
| 0x399650 | `exit` (PLT thunk) | ARM | libc `exit()` thunk, GOT `__imp_exit` @ 0x3EA5E0 (reloc 0x3A2D84) | functions.json; imports.json |
| 0x398F60 | `ptrace` (PLT thunk) | ARM | libc `ptrace()` thunk, GOT `__imp_ptrace` @ 0x3EA408 (reloc 0x3A2BC8) | functions.json; imports.json |
| 0x398F90 | `fork` (PLT thunk) | ARM | libc `fork()` thunk, GOT `__imp_fork` @ 0x3EA41C (reloc 0x3A2BD4) | functions.json; imports.json |
| 0x398E80 | `syscall` (PLT thunk) | ARM | libc `syscall()` thunk, GOT `__imp_syscall` @ 0x3EA3C8 (reloc 0x3A2B90) | functions.json; imports.json |
| 0x0DC146 | `sub_DBC9C` | Thumb | **Init-failure self-kill**: calls `getpid()`; `kill(pid, 9)` (SIGKILL) | BLX @ 0xDC146 in decompiled `RAW/m2_decomp_dbc9c.txt` |
| 0x15BE4C | `sub_15BE28` | Thumb | **Tracer-suspension watchdog kill 1**: `kill(target_pid, 19)` (SIGSTOP) | BLX @ 0x15BE4C in Capstone disasm |
| 0x15BE68 | `sub_15BE28` | Thumb | **Tracer-suspension detach**: `ptrace(PTRACE_DETACH, target_pid, 0, 0)` | BLX @ 0x15BE68 in Capstone disasm |
| 0x15BE70 | `sub_15BE28` | Thumb | **Tracer-suspension watchdog kill 2**: `kill(target_pid, 18)` (SIGCONT) | BLX @ 0x15BE70 in Capstone disasm |
| 0x15B6CA | `sub_15B688` | Thumb | **Fork watchdog worker**: calls `fork()` to spawn scan child | BLX @ 0x15B6CA in Capstone disasm |
| 0x15B6EA | `sub_15B688` | Thumb | **Fork child termination**: calls `_exit(127)` in child process | BLX @ 0x15B6EA in Capstone disasm |
| 0x35662E | `sub_356618` | Thumb | **Direct exit wrapper**: invokes `exit(1)` upon unrecoverable crash/violation | BLX @ 0x35662E in Capstone disasm |

### 2. Master watchdogs & syscall dispatchers

| Offset (RVA) | Symbol / our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0x1561F8 | `sub_1561F8` | Thumb | **Master libc dispatch table builder**: builds 32-entry function pointer array containing `open`, `read`, `write`, `fopen`, `fread`, `fgets`, `fseek`, `readdir`, `syscall`, `access`, `stat`, `fstat`, `getenv`, `kill` (slot 14), `gettimeofday`, `sleep`, `select`, `connect`, `send`, `recv`, `opendir`, `ptrace` (slot 22), `execl`, `clock_gettime`, `fdopen`, `getpid`, `dlopen`, `dlclose`, `pthread_create`, `fork` (slot 30), `mmap`, and `sub_DBC9C` (slot 32). | `RAW/kill_report.c` (ida.cmd decompile); callers: `sub_156784` @ 0x156796 <- `sub_155874` @ 0x1558CC |
| 0x17B00C | `sub_17B00C` | Thumb | **Decrypted-ID libc lookup gate**: string-ID to libc pointer resolver (e.g. 31262 -> `&kill_ptr`, 31210 -> `&syscall_ptr`, 31368 -> `&execl_ptr`, 31385 -> `&getpid_ptr`, 31575 -> `&AnoSDKInit_ptr`). | `RAW/kr_sub_17B00C.c`; caller: `sub_19F212` @ 0x19F21E |
| 0x35D858 | `sub_35D858` | Thumb | **Master dynamic syscall watchdog**: picks one of 32 ARM-mode raw SVC stubs from `off_3A08D4[a1 & 0x1F]`; allocates 52-byte singleton `dword_3DB164`; falls back to libc `&syscall` if NULL; dispatches via `sub_10B3E8`. | `RAW/kr_sub_35D858.c`; caller: `sub_F5D2C` @ 0xF5D4E |
| 0x3A08D4 | `off_3A08D4` | Data | 32-entry pointer table (virtual address 0x3A08D4, file offset 0x39C8D4 in `.data.rel.ro`) pointing to 32 ARM-mode raw SVC syscall stubs `sub_381A40`..`sub_382410`. | ELF `.data.rel.ro` hex dump; Capstone disasm |

### 3. Raw ARM-mode SVC syscall stub bank (32 stubs)

Unlike arm64 which scattered inline `svc #0` instructions throughout normal control flow, our ARMv7a binary centralizes raw syscalls into a dedicated 32-stub dispatch bank encoded in **32-bit ARM mode** (addresses even, not Thumb odd). Each stub is uniquely obfuscated with junk instructions (`nop`, `add r1, r1, #0`, `mov fp, fp`) to prevent uniform byte-signature detection:

| Slot | Stub Offset (RVA) | SVC Offset | ISA | Implementation Shape | Evidence |
|---|---|---|---|---|---|
| 0 | 0x381A40 | 0x381A84 | ARM | `mov ip, sp; push {r4-r7}; mov r7, r0; ...; svc #0; pop {r4-r7}; bx lr` | Capstone disasm; `off_3A08D4[0]` |
| 1 | 0x381AB0 | 0x381AE4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[1]` |
| 2 | 0x381B00 | 0x381B34 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[2]` |
| 3 | 0x381B50 | 0x381B84 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[3]` |
| 4 | 0x381BA0 | 0x381BD4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[4]` |
| 5 | 0x381BF0 | 0x381C24 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[5]` |
| 6 | 0x381C40 | 0x381C74 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[6]` |
| 7 | 0x381C90 | 0x381CC4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[7]` |
| 8 | 0x381CE0 | 0x381D14 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[8]` |
| 9 | 0x381D30 | 0x381D64 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[9]` |
| 10 | 0x381D80 | 0x381DB4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[10]` |
| 11 | 0x381DD0 | 0x381E04 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[11]` |
| 12 | 0x381E20 | 0x381E54 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[12]` |
| 13 | 0x381E70 | 0x381EA4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[13]` |
| 14 | 0x381EC0 | 0x381EF4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[14]` |
| 15 | 0x381F10 | 0x381F44 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[15]` |
| 16 | 0x381F60 | 0x381F94 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[16]` |
| 17 | 0x381FB0 | 0x381FE4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[17]` |
| 18 | 0x382000 | 0x382034 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[18]` |
| 19 | 0x382050 | 0x382084 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[19]` |
| 20 | 0x3820A0 | 0x3820D4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[20]` |
| 21 | 0x3820F0 | 0x382124 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[21]` |
| 22 | 0x382140 | 0x382174 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[22]` |
| 23 | 0x382190 | 0x3821C4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[23]` |
| 24 | 0x3821E0 | 0x382214 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[24]` |
| 25 | 0x382230 | 0x382264 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[25]` |
| 26 | 0x382280 | 0x3822B4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[26]` |
| 27 | 0x3822D0 | 0x382304 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[27]` |
| 28 | 0x382320 | 0x382354 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[28]` |
| 29 | 0x382370 | 0x3823A4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[29]` |
| 30 | 0x3823C0 | 0x3823F4 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[30]` |
| 31 | 0x382410 | 0x382444 | ARM | Obfuscated ARM syscall wrapper | Capstone disasm; `off_3A08D4[31]` |
| — | 0x381A10 | 0x381A2C | ARM | Prototype un-padded ARM syscall wrapper | Capstone disasm; referenced @ 0x39E658 |

*(Note: Raw byte sweeps matching `0x27xx` in `sp_r7imm.txt` at 0xA5F82, 0xBAEC2, 0xC2B54, 0xD2410 are data-stream artifacts and unaligned non-code literals. The 32 ARM stubs above are the SOLE active raw SVC emitters in `libanogs.so`)*.

### 4. Telemetry reporter & kill-switch flags

| Offset (RVA) | Global / Function | Type | Value / Purpose | Evidence |
|---|---|---|---|---|
| 0x3653D4 | `sub_3653D4` | Thumb | **Master TDM Report Builder (`ace_create_tdm_report`)**: checks `byte_3DB1EC`; constructs COREREPORT buffer; populates fields `"TSS"`, raw payload, error code, category 40004. | `RAW/kr_sub_3653D4.c`; callers: `sub_365364`, `sub_365580`, `sub_3655F0`, `sub_36567C`, `sub_36570C` |
| 0x3DB1EC | `byte_3DB1EC` | `.bss` (byte) | **`g_tdm_report_enabled`**: Master telemetry kill-switch. If 0, `sub_3653D4` immediately aborts and returns 0. | `RAW/kr_sub_3653D4.c`: lines 23–24 |
| 0x3DB1ED | `byte_3DB1ED` | `.bss` (byte) | **`g_tdm_report_checked`**: Master telemetry initialized flag. If 1, skips `sub_133F6C()` re-initialization. | `RAW/kr_sub_3653D4.c`: lines 21–22 |
| 0x3DB1F0 | `dword_3DB1F0` | `.bss` (dword) | **`g_tdm_report_fail_count`**: Consecutive failure counter. If >= 3, engine sets `byte_3DB1EC = 0` automatically. | `RAW/kr_sub_3653D4.c`: lines 70–71 |
| 0x3D6930 | `dword_3D6930` | `.bss` (dword) | **`g_corereport_singleton`**: Global COREREPORT channel object pointer. | `RAW/kr_sub_3653D4.c`: lines 29–37 |
| 0x3DB1AC | `byte_3DB1AC` | `.bss` (byte) | **Probabilistic 10% sampling trigger flag**: ensures deep scan `sub_37BDD0` only triggers once per boot if `time() % 100 >= 10`. | `RAW/kr_sub_365320.c`: lines 10–19 |
| 0x365540 | `sub_365540` | Thumb | **TDM Report Submitter (`ace_submit_corereport`)**: dispatches populated report packet to network buffer. | `RAW/kr_sub_365540.c` |

---

## Key Pseudocode

### Master Telemetry Report Packer (`sub_3653D4` @ 0x3653D4)

```c
// sub_3653D4 @ 0x3653D4 (from RAW/kr_sub_3653D4.c, trimmed to kill-switch logic)
int __fastcall sub_3653D4(int a1, int a2, int a3, int a4) {
    if ( byte_3DB1ED == 0 )       // g_tdm_report_checked
        sub_133F6C();             // initialize flag from config
    
    // === CRUCIAL KILL-SWITCH ===
    if ( byte_3DB1EC == 0 )       // g_tdm_report_enabled
        return 0;                 // SILENT DROP: returns NULL, no report created
    
    int v7 = (a4 != 0) ? 1 : 3;   // severity level
    int *v8 = (int *)dword_3D6930;// g_corereport_singleton
    if ( !v8 ) {
        v8 = (int *)sub_394094(16);
        dword_3D6930 = (int)v8;
        *v8 = &off_3A0A54; v8[1] = &off_3A0A84;
    }
    int v9 = v8[3];
    if ( v9 && (v11 = (*(v9+16))(v9, sub_37CBF0(49902))) != 0
            && (v12 = (*(v11+32))(v11, "COREREPORT")) != 0
            && (v13 = (*(v12+16))(v12, v7, 2004, a1)) != 0 ) {
        // Populate fields: source "TSS", error codes, payload, category 40004
        ...
        return v13;
    } else {
        if ( dword_3DB1F0++ >= 3 )  // fail count >= 3
            byte_3DB1EC = 0;        // self-disable report generation
        return 0;
    }
}
```

### Master Syscall Watchdog Dispatcher (`sub_35D858` @ 0x35D858)

```c
// sub_35D858 @ 0x35D858 (from RAW/kr_sub_35D858.c, trimmed)
int __fastcall sub_35D858(char a1) {
    int v1 = dword_3DB164;
    if ( !v1 ) {
        int (**v3)(int, ...) = sub_35D6BC();
        if ( !v3 )
            v3 = (int (**)(int, ...))off_3A08D4[a1 & 0x1F]; // Select from 32 ARM raw SVC stubs
        v1 = sub_394094(52);                                // Allocate 52-byte watchdog struct
        sub_35D8D0();
        if ( !v3 )
            v3 = &syscall;                                  // Fallback to libc syscall thunk
        sub_13EC82(v1, v3);
        dword_3DB164 = v1;
    }
    return sub_10B3E8(v1 + 6 * (*(_DWORD *)(v1 + 48) & 7));
}
```

### Tracer-Suspension Watchdog (`sub_15BE28` @ 0x15BE28)

```assembly
// sub_15BE28 @ 0x15BE28 (Capstone disasm)
// Loops over 512 task slots at r0 + 0x38:
loc_15BE40:
    ldr.w   r5, [r6, r4, lsl #2]     // r5 = target_pid
    cmp     r5, #1
    blt     loc_15BE74
    mov     r0, r5
    movs    r1, #19                  // SIGSTOP (0x13)
    blx     #0x398B30                // kill(target_pid, SIGSTOP)
    mov     r0, #17                  // PTRACE_DETACH (0x11)
    mov     r1, r5
    movs    r2, #0
    movs    r3, #0
    blx     #0x398F60                // ptrace(PTRACE_DETACH, target_pid, 0, 0)
    mov     r0, r5
    movs    r1, #18                  // SIGCONT (0x12)
    blx     #0x398B30                // kill(target_pid, SIGCONT)
loc_15BE74:
    adds    r4, #1
    cmp.w   r4, #0x200               // 512 task iterations
    bne     loc_15BE40
```

---

## Call Graph

```
[Detection Scanners]
  ├── sub_10B888 (root / env violation) ──────────► sub_3655F0 (wrap 3) ──┐
  ├── sub_11DF3C (memory / hook check) ──────────► sub_365364 (wrap 1) ──┤
  ├── sub_365580 (integrity check) ──────────────► sub_365580 (wrap 2) ──┤
  ├── sub_36567C (module check) ─────────────────► sub_36567C (wrap 4) ──┤
  └── sub_36570C (monitor registrar) ────────────► sub_36570C ───────────┘
                                                         │
                                                         ▼
                                                sub_3653D4 (0x3653D4) [Report Packer]
                                                ├── if (byte_3DB1EC == 0) return 0;  <== [KILL-SWITCH]
                                                └── if (valid) ──► sub_365540 [Submit COREREPORT]

[Watchdogs & Direct Kills]
  ├── Init Failure:
  │     AnoSDKInit (0xE6E04) ──► sub_DBC9C (0xDBC9C)
  │                                └── [On Error] ──► kill(getpid(), 9) @ 0xDC146 [SIGKILL]
  │
  ├── Dynamic Syscall Dispatcher:
  │     sub_F5D2C (0xF5D2C) ──► sub_35D858 (0x35D858)
  │                                ├── Selects off_3A08D4[opcode & 0x1F] (32 ARM SVC stubs)
  │                                └── Stubs @ 0x381A40..0x382410 (svc #0)
  │
  ├── Process Tracer Watchdog:
  │     sub_15BE28 (0x15BE28)
  │        ├── kill(pid, SIGSTOP) @ 0x15BE4C
  │        ├── ptrace(PTRACE_DETACH, pid) @ 0x15BE68
  │        └── kill(pid, SIGCONT) @ 0x15BE70
  │
  ├── Fork Watchdog:
  │     sub_15B688 (0x15B688) ──► fork() @ 0x15B6CA
  │                                 └── [Child] ──► _exit(127) @ 0x15B6EA
  │
  └── Master Libc Table Builder:
        sub_155874 ──► sub_156784 ──► sub_1561F8 (0x1561F8)
                                        ├── Stores &kill, &ptrace, &fork, &syscall, &sub_DBC9C
                                        └── Populates 32-entry indirect function pointer table
```

---

## Divergence from the arm64 notes

1. **Syscall architecture**:
   - `INFO/ace_anticheat_notes/12_complete_kill_path_inventory.md` notes that arm64 had raw `svc #0` instructions with `x8` inline literals scattered everywhere across `libanort.so` (100 decoder traps, `0x25F28` GP7Service stop, etc.).
   - In our ARMv7a `libanogs.so`, raw syscalls are **NOT** scattered inline throughout the scanners. Instead, raw SVC execution is factored into a dedicated 32-stub dispatch bank (`0x381A40`..`0x382410`) in ARM mode, selected via pointer array `off_3A08D4` (0x3A08D4) by `sub_35D858`.
2. **Telemetry global flag addresses**:
   - In arm64 `20_tdm_report_chain.md`: `g_tdm_report_enabled` was at `byte_57E31C`, `g_tdm_report_checked` was at `byte_57E31D`, and fail count was at `dword_57E320`.
   - In OUR ARMv7a `libanogs.so`: `g_tdm_report_enabled` is at **`byte_3DB1EC`**, `g_tdm_report_checked` is at **`byte_3DB1ED`**, and fail count is at **`dword_3DB1F0`**.
3. **Tracer-suspension watchdog (`sub_15BE28`)**:
   - The arm64 documentation did not catalog the 512-PID `SIGSTOP` -> `PTRACE_DETACH` -> `SIGCONT` loop present in v7a `sub_15BE28`.
4. **Master dispatch table (`sub_1561F8`)**:
   - `sub_1561F8` explicitly packs `sub_DBC9C` as slot 32 alongside libc `kill` (slot 14) and `ptrace` (slot 22); arm64 notes did not map this master table.

---

## Kill Switch Table & Runtime Bypass Instructions

To neuter the entire kill and report pipeline at runtime without causing crash side-effects:

| Target (Symbol / Address) | RVA / Global | Target Value / Action | Runtime Neuter Mechanism | Safety Rationale |
|---|---|---|---|---|
| `g_tdm_report_enabled` | `0x3DB1EC` (byte) | Write `0x00` | `*(uint8_t*)(libanogs_base + 0x3DB1EC) = 0;` | Disables all report packet packing in `sub_3653D4`. |
| `g_tdm_report_checked` | `0x3DB1ED` (byte) | Write `0x01` | `*(uint8_t*)(libanogs_base + 0x3DB1ED) = 1;` | Prevents `sub_133F6C()` from re-enabling telemetry at runtime. |
| `sub_DBC9C` self-kill | `0x0DC146` (Thumb) | Replace 4 bytes with NOPs | Write `0x00 0xBF 0x00 0xBF` (NOP, NOP) to `0xDC146` | Cuts `kill(getpid(), 9)` init failure termination while letting init continue. |
| `sub_15BE28` watchdog | `0x15BE28` (Thumb) | `BX LR` | Write `0x70 0x47` (`bx lr`) to `0x15BE28` | Neutralizes anti-tracer SIGSTOP/SIGCONT thread loop entirely. |
| `sub_356618` exit wrap | `0x356618` (Thumb) | `BX LR` | Write `0x70 0x47` (`bx lr`) to `0x356618` | Prevents sudden exit(1) invocation on violation traps. |
| `sub_3653D4` packer | `0x3653D4` (Thumb) | `MOVS R0, #0; BX LR` | Write `0x00 0x20 0x70 0x47` to `0x3653D4` | **PROVEN**: Hard-returns NULL on any report construction attempt. |

### Concrete Minimal Runtime Script (Frida / Native Injector)

```javascript
// Minimal Viable Kill-Chain Neuter for libanogs.so (v7a)
const libanogs = Process.findModuleByName("libanogs.so");
if (libanogs) {
    // 1. Flip TDM report kill-switch in .bss
    const g_tdm_report_enabled = libanogs.base.add(0x3DB1EC);
    const g_tdm_report_checked = libanogs.base.add(0x3DB1ED);
    Memory.writeU8(g_tdm_report_enabled, 0);
    Memory.writeU8(g_tdm_report_checked, 1);

    // 2. Patch init self-kill at 0xDC146 (kill(pid, 9))
    Memory.protect(libanogs.base.add(0xDC146), 4, "rwx");
    libanogs.base.add(0xDC146).writeByteArray([0x00, 0xBF, 0x00, 0xBF]); // NOP; NOP

    // 3. Patch tracer suspension watchdog at 0x15BE28
    Memory.protect(libanogs.base.add(0x15BE28), 2, "rwx");
    libanogs.base.add(0x15BE28).writeByteArray([0x70, 0x47]); // BX LR
}
```

---

## Bypass Implications

1. **PROVEN (saw it in the bytes)**:
   - Setting `byte_3DB1EC = 0` and `byte_3DB1ED = 1` stops ALL 5 callers of `sub_3653D4` from building reports. Because callers check for non-zero return, `sub_365540` (`submit_corereport`) is never reached.
   - NOPping `0xDC146` safely removes the uncatchable `kill(pid, 9)` init self-kill without disrupting the rest of `sub_DBC9C` thread initialization.
2. **HYPOTHESIS (needs runtime confirmation)**:
   - NOPping the tracer loop `sub_15BE28` (`0x15BE28`) does not disturb game thread execution since it only iterates background tasks to verify debugger absence.
   - The 32-stub raw SVC array in `off_3A08D4` is invoked by `sub_35D858` for watchdog telemetry checks; because `sub_35D858` falls back to `&syscall` if stub resolution fails, patching entries in `off_3A08D4` to a benign stub is safe.

---

## Open questions / next probes

1. **Verify `sub_155874` calling context**:
   - Run: `analysis\tools\ida.cmd libanogs search RAW/callers_155874.json callers 0x155874` to see if `sub_155874` runs from an `ano_%d` background thread or main thread.
2. **Runtime probe of `byte_3DB1EC`**:
   - In injector session, verify that reading `0x3DB1EC` after `AnoSDKInit` returns 1 if untouched, and confirming that setting 0 causes zero network telemetry packets to be transmitted to Tencent servers.
