# libanogs.so — Init flow & boot sequence (our v7a analysis)

> Source of truth: OUR analysis/libanogs/libanogs.so (md5 2810a533, from IDENTITY.txt).
> Cross-ref hint (verify, don't trust): INFO/ace_anticheat_notes/30_libanogs_init_array.md
> and 00_TLDR_FULL_SYSTEM.md init section — arm64 + UE4 build, different offsets and some
> logic differences (see "Divergence").

## Summary

libanogs boots in three stages: (1) 67 Thumb init_array ctors run at `dlopen` and only set
up state (singletons, mutexes, the JNI method table) — no detection logic; (2) `JNI_OnLoad`
registers the Java bridge; (3) the game calls `AnoSDKInit`, which is the SINGLE boot entry
that arms detection: it runs the obfuscated core-init (`sub_DBC9C`, which wires the report
handshake, spawns `ano_%d` worker threads and contains a `kill(getpid(), 9)` self-kill
branch) and then registers monitor modules (`sub_36570C`). PROVEN at runtime: NOPping
`AnoSDKInit` to `return 0` freezes FF's resource download forever (STATUS.md 2026-09-01) —
FF blocks on an ACE handshake callback that never fires. **Never neuter ACE statically.**

## Evidence — stage 1: init_array (67 ctors, slot_eas 0x3A23B4→0x3A24AC)

All 67 are Thumb stubs ≤40 bytes (sizes from functions.json; 66 of 67 are <28 bytes).
None contain detection logic — they build module state and register `__cxa_atexit` cleanup,
matching the arm64 note's pattern. Evidence: init_array.json + decompiles in
`RAW/m2_c_*.txt`.

| Slot | Ctor RVA | What it sets up | Evidence |
|---|---|---|---|
| 0 | 0xEF18C | **JNI native-method table builder** (the big one). Decrypts Java method names/sigs via the string-decoder family (`sub_380220(2970)`, `sub_3807B4(2977)`, … ids 2970–3140) into globals `dword_3D2074…3D20F4`, paired with native handlers `sub_EE134, sub_EE260, sub_EE470, sub_EE700, sub_EE78C, sub_EE958, sub_EE9FC, sub_EEA70, sub_EEBC4, sub_EED1C, sub_EEDB8`. One plaintext pair survives: `"setappobject"` / `"(ILjava/lang/Object;)I"` at `dword_3D20EC/3D20F0`. | RAW/m2_c_EF18C.txt (ida.cmd decompile) |
| 13 | 0x1E631C | Generic module-singleton init: `sub_1BAB80(&unk_3D6DFC)` + `__cxa_atexit(sub_1BAC1C, …)`. NOT the ob_zip-filename ctor our arm64 hint shows. | RAW/m2_c_1E62C0.txt |
| 11 | 0x1CF0DC | Chain of 4 tiny helpers (state init + cleanup registration). | RAW/m2_c_1CF0DC.txt |
| 59 | 0x30946C | Chain of 3 tiny helpers — same pattern. | RAW/m2_c_30946C.txt |
| 16 | 0x2000D0 | Chain of 3 tiny helpers — same pattern. | RAW/m2_c_2000D0.txt |
| 22 | 0x248A9C | 2-helper state init — same pattern. | RAW/m2_c_248A9C.txt |
| 38 | 0x313210 | 1-helper state init — same pattern. | RAW/m2_c_313210.txt |
| — | 0xF11B0 | `pthread_once`-guarded singleton, allocates a 188-byte global object (callees `pthread_once`, `sub_394094`, `sub_F124C`) — the shared env/state singleton used across init. | RAW/m2_c_F11B0.txt |

Obfuscation note (PROVEN in our bytes): two shared indirect-branch trampolines exist —
`sub_1AB238` (48 xrefs) and `sub_133F6C` (497 xrefs), both `__noreturn` ending in
`MOV PC, R1/R2` with a flag-checked constant (`dword_3D6928`, `dword_3D25C0`). Our v7a
build uses tail-branch dispatch; the arm64 notes never mention this shape.

## Evidence — stage 2/3: AnoSDKInit → detection boot

| Offset (RVA) | our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0xE6E04 | AnoSDKInit | Thumb | Exported init (game_id). Opaque-constant-flattened wrapper; real work: `sub_DD960(a1)` then `sub_36570C(a1 > -1, 0)`. | RAW/m2_decomp_batch1.txt |
| 0xDD960 | sub_DD960 | Thumb | Builds core-init arg struct `{12, game_id, 0, …}` and tail-calls `sub_DBC9C(v20)`. | RAW/m2_decomp_dd960.txt |
| 0xDBC9C | sub_DBC9C | Thumb | **Core init.** Sets `byte_3D2064 = 1` (init-started flag); fills `init_info` via `sub_37C15C`; stores `*(game_id+8)` into `off_3A6E04`; spawns a worker via `sub_11DDE8` + `sub_36C354` (thread named `ano_%d`, see 0x36C2C8); on one branch calls `getpid(); kill(pid, 9)` — init-failure self-kill. | RAW/m2_decomp_dbc9c.txt |
| 0x37C15C | sub_37C15C | Thumb | `init_info` builder: wires the `tss_sdk_send_data_to_svr` callback (debug string `"init_info->tss_sdk_send_data_to_svr:%p"` @ 0x60A90, xrefs 0x37C1A8–0x37C1D8 land inside this fn). This is the report-channel handshake FF blocks on. | strings.json 0x60A90; fn-of via functions.json |
| 0x36C2C8 | sub_36C2C8 | Thumb | Detection thread namer/spawner helper: plaintext `"ano_%d"` @ 0x63468, xrefs 0x36C308–0x36C32C; 31 xrefs_to = the generic thread-launch helper. Where ACE's `ano_0..N` worker threads are born. | strings.json 0x63468 |
| 0x36570C | sub_36570C | Thumb | **Monitor registrar.** Opcode 0–6 dispatch with one-shot flags `dword_3DB1C4[opcode]`; per opcode builds a monitor object from an encrypted string id (0→33682 `sub_380BB0`, 1→33695 `sub_38160C`, 2→33715 `sub_37D64C`, 3→33731 `sub_37E30C`, 4→33748 `sub_37F098`, 5→33770 `sub_380220`, 6→33792 `sub_3813A8`), registers it as `"monitor"` via `sub_3653D4`, calls vtable `*(obj)+20` (= slot 5 — the init override in the arm64 base-vtable map), and appends to the global monitor list `dword_3D6930` via `sub_365540`. AnoSDKInit invokes it with opcode 0. | RAW/m2_decomp_36570c.txt |

Key pseudocode (trimmed):

```c
// AnoSDKInit @ 0xE6E04  (RAW/m2_decomp_batch1.txt, deobfuscated flow)
sub_DD960(a1);            // -> sub_DBC9C({12, game_id, 0})
sub_36570C(a1 > -1, 0);   // register monitor module #0 (encrypted string id 33682)

// sub_36570C @ 0x36570C (trimmed)
if ( dword_3DB1C4[a2] == 0 ) {
    dword_3DB1C4[a2] = 1;
    switch ( a2 ) { case 0: result = sub_380BB0(33682); /* ids 33682..33792 */ }
    result = sub_3653D4((int)"monitor", v5, a1, 1);
    (*(void (**)(int *))(*result + 20))(result);   // vtable slot 5: module init
    return sub_365540(v6 + 1, (int)&v7);           // append to dword_3D6930 list
}

// sub_DBC9C @ 0xDBC9C (trimmed — the kill branch)
v12 = getpid();
kill(v12, 9);              // init-failure self-kill, uncatchable via libc signal handling
```

## How it fires / call graph

```
dlopen(libanogs.so)
  └─ 67 init_array ctors (0x3A23B4..0x3A24AC) — state only, no detection
       └─ slot0 sub_EF18C: builds JNI native-method table (globals 0x3D2074..0x3D20F4)
JNI_OnLoad @ 0xEECB4 (export)
  └─ sub_1AB238 → MOV PC,R1 tail-dispatch (branch-obfuscated; RegisterNatives path not
     statically resolvable by the decompiler — A1's surface, see Open questions)
game calls AnoSDKInit(game_id) @ 0xE6E04
  ├─ sub_DD960 @ 0xDD960 → sub_DBC9C @ 0xDBC9C   ← detection STARTS here
  │    ├─ byte_3D2064 = 1; off_3A6E04 = ctx+8
  │    ├─ sub_37C15C: init_info + tss_sdk_send_data_to_svr callback  (report handshake)
  │    ├─ sub_11DDE8 + sub_36C354 → sub_36C2C8: spawn "ano_%d" worker threads
  │    └─ [failure branch] getpid(); kill(pid,9)
  └─ sub_36570C @ 0x36570C(opcode 0): arm monitor module #0 (string id 33682)
       └─ (later opcodes 1–6 arm monitors 33695..33792 — via the 24 callers of sub_36570C,
          incl. AnoSDKIoctl/AnoSDKIoctlOld region — GUESS, callers list not fully traced)
```

**The SINGLE detection-start function: `sub_DBC9C` @ 0xDBC9C** (via AnoSDKInit →
sub_DD960). It is the first place a detection worker thread is spawned; `sub_36570C` then
arms the monitor modules. `AnoSDKInit` is the single *boot entry* that reaches both.

## MUST-STAY-ALIVE vs SAFE-TO-NEUTER

| Step | Verdict | Basis |
|---|---|---|
| `AnoSDKInit` export @ 0xE6E04 | **MUST-STAY-ALIVE (PROVEN)** | Runtime test on BlueStacks: `return 0` stub → FF resource download freezes at chunk 1 forever, ANR (STATUS.md 2026-09-01, 3-way isolation). FF waits for an ACE handshake callback that only fires after init completes. |
| `sub_DBC9C` core-init @ 0xDBC9C + `sub_37C15C` init_info wiring @ 0x37C15C | **MUST-STAY-ALIVE (PROVEN-by-dependency)** | The `tss_sdk_send_data_to_svr` handshake is inside the chain FF blocks on; skipping any of it = the observed freeze. Static proof only (same chain, no runtime isolation test per-function). |
| All 67 init_array ctors | **MUST-STAY-ALIVE (PROVEN static shape, HYPOTHESIS on consequences)** | Pure state init; arm64 note says init failure is trapped by exit_group paths. Our build not runtime-tested per-ctor. They are cheap — leave them. |
| `JNI_OnLoad` @ 0xEECB4 | **MUST-STAY-ALIVE (PROVEN-by-dependency)** | It is the loader entry; without it no Java bridge, no callbacks FF awaits. |
| Monitor modules 1–6 in `sub_36570C` (string ids 33695/33715/33731/33748/33770/33792) | **SAFE-TO-NEUTER (HYPOTHESIS)** | Skipping later opcodes should degrade detection, not boot — opcode 0 arms during init, FF's handshake does not await monitors 1–6. UNTESTED. Moot: our strategy is ACE-alive (STATUS.md pivot). |
| `kill(getpid(), 9)` branch inside `sub_DBC9C` | **SAFE-TO-NEUTER (HYPOTHESIS)** | It is ACE self-terminating on an init anomaly; NOPping the branch helps US survive an anomaly, does not break the handshake. Byte-level patch site not yet pinned (Open question). UNTESTED. |
| `ano_%d` worker threads (via `sub_36C2C8`) | **DO NOT NEUTER** | These ARE the detection threads. Neutering statically would be detected by ACE's integrity self-checks (see A5's kill chain; HYPOTHESIS) and contradicts the ACE-alive strategy. |

## Divergence from the arm64 notes

- Offsets differ wholesale (expected): their `AnoSDKInit` 0x1DA368 vs our 0xE6E04; their
  JNI_OnLoad 0x1E2444 vs our 0xEECB4; 60 ctors vs our 67.
- Logic divergence (PROVEN in our bytes): their `init_ctor_03` @ 0x1E6F88 decrypts the six
  `ob_*.zip` filenames. Our slot-13 ctor @ 0x1E631C is a **generic** singleton init
  (`sub_1BAB80(&unk_3D6DFC)` + `__cxa_atexit`) — no string-decoder calls. The ob_zip
  filename decryption in OUR build is not yet located (TODO, needs A3's decoder dump — the
  decoder family IS here: `sub_380BB0/sub_380220/…` take encrypted ids).
- Their "init_ctor_02 builds the JNI native method table" — in OUR build that is
  **slot 0** (`sub_EF18C` @ 0xEF18C), and the table lands in `dword_3D2074…3D20F4` with 11
  handlers, matching their "11 methods" claim.
- Their notes describe `ace_pthread_create_detached` in libanort; our v7a libanogs spawns
  `ano_%d`-named threads via `sub_36C2C8` — the naming scheme is the same family
  (`ano_%d` @ 0x63468).

## Bypass implications

1. **PROVEN: static ACE neutering is a dead end.** Any stub of `AnoSDKInit` (or anything on
   the `sub_DBC9C`→`sub_37C15C` handshake chain) freezes boot. The only winning strategy is
   ACE fully alive + runtime stealth of our own artifacts (STATUS.md 2026-09-01 pivot).
2. If we ever need surgical in-init edits, the only *plausibly* safe byte-level targets are
   (a) the `kill(getpid(),9)` branch in `sub_DBC9C` and (b) the opcode 1–6 arms in
   `sub_36570C` — both HYPOTHESIS, both need a BlueStacks A/B test before shipping.
3. The init chain tells us where every monitor module's one-shot flag lives:
   `dword_3DB1C4[0..6]` @ 0x3DB1C4. Those flags are read-once guards — if a runtime hook
   wants to silently skip a monitor, its flag is the lever (HYPOTHESIS — verify with A4's
   per-module analysis before touching).
4. Thread naming (`ano_%d`) gives us a runtime tripwire: any thread named `ano_*` in
   `/proc/<pid>/task/*/comm` is ACE. Useful for our crash_probe/log filtering — NOT for
   hiding (they can read their own names back).

## Open questions / next probes

1. Pin the exact byte offset of the `kill(getpid(),9)` branch in `sub_DBC9C`:
   `analysis\tools\ida.cmd libanogs search RAW\m2_s_svc.json svc` (A5 runs this anyway —
   the `kill` site near 0xDBC9C is ours) then disassemble the branch.
2. Resolve `JNI_OnLoad`'s tail-dispatch (`sub_1AB238`, `MOV PC,R1`): read raw bytes at
   0x1AB238–0x1AB2A0 to find the R1 constants, or better: A1's RegisterNatives search
   (`ida.cmd libanogs search RAW\jni_reg.json str RegisterNatives` / xref the ctor table
   at 0x3D2074) will find the registration fn without tracing the dispatcher.
3. Which function drives monitor opcodes 1–6 (24 callers of `sub_36570C`):
   `python` fn-of on the 24 xrefs of 0x36570C from functions.json — 2-probe rule hit here,
   deferred.
4. A3 dependency: decode string ids 2970–3140 (JNI table) and 33682–33792 (monitor names)
   to name each monitor module → merges this note with A4's detection inventory.
