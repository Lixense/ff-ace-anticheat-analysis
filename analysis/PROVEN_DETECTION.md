# ACE DETECTION — PROVEN in our v7a bytes (workflow ace-detection-hunt, 2026-09-02)

> 21 agents, 0 errors. Every offset cited was decompiled from OUR libanogs.so.i64 /
> libanort.so.i64 via ida_snap.cmd and adversarially re-verified. ZERO arm64-notes used.

## Ban root causes (ranked, byte-proven)

1. #1 MODIFIED base.apk FILE HASH (surface b) — strongest, most-corroborated. Read by TWO independent libs via multiple routines: libanogs CRC sub_231B44@0x231B44 (maps a module segment and CRCs it) reached from dispatcher sub_23267C@0x23267C opcodes 3/0x18/0x1A/0x1B; libanogs sub_30F820@0x30F820 reconstructs /data/app/%s-%d/base.apk from maps; libanort sub_5B87C@0x5B87C fopen+fread+checksum(sub_EA634)->code 58->sink sub_60D86@0x60D86. Verdict bundled in obfuscated field 'cert_md5=%s|apk_hash_1|apk_hash_2|txt_seg_crc' (decoded_strings.txt:1775, ~0x5F5C9). PROVEN client-side (imports.json: openat/mmap/fstat present). Unbeatable at runtime because sub_35CF60@0x35CF60 re-reads the on-disk file fresh, not a memory copy.

2. #2 RE-SIGNED CN=Debug CERT (surface a) — very strong, caught by both libs and below the LSPatch layer. libanogs local self-computed 'cert_md5' from the same mmap CRC path (obfuscated, primary/harder) PLUS a weaker JNI path 'CertMD5=%s|CertAuthorB64=%s|'@0x5F4DA fed via export AnoSDKOnRecvSignature->sub_E0D0C@0xE0D0C. libanort sub_851D8@0x851D8 decodes 'APK Sig Block 42' and parses the v2 signing block NATIVELY from the APK on disk — this defeats LSPatch --sigbypass, which only covers the Java PackageManager check. Our CN=Debug cert differs from Garena's and is caught by all three.

3. #3 DOBBY / INLINE .text HOOKS (technique, conditional — fires only if our .so inline-hooks a scanned module). PROVEN detectors exist: libanogs sub_17A590@0x17A590 memcmp's live pages vs on-disk file (cmp primitive sub_34EE46@0x34EE46, zero tolerance), sub_2E7DF0@0x2E7DF0 mprotects r-xp RWX and CRCs it (sub_394EEC); mismatches recorded by sub_378E6C@0x378E6C ('!skip:0x%08x,bin_patch_cnt:%d'); dispatcher sub_24BC4C@0x24BC4C codes 10/11 -> set_inline_hook_error/inline_hook_opcode_dismatch -> reporter sub_24B8FC@0x24B8FC -> shared queue loc_D99B0(56). libanort sub_F368E@0xF368E walks ELF32 section headers and reports md5_crc32 of .text; libc-pointer enumerator libanogs sub_1561F8@0x1561F8 checks open/read/ptrace/mmap etc. Whether this bans us depends on OUR implementation choice, so it is a hard DO-NOT rather than a current-ship certainty.

4. #4 EXTRA libmedia_codec.so IN /proc/self/maps (surface c) — WEAKEST real surface; partly GUESS. PROVEN the literal name BLOCKLIST (libanogs @0xC5324: frida/xposed/sandhook/hookzz/whale/epic/xhook) does NOT contain libmedia_codec (grep = 0 hits), so the name-match path never fires. The maps enumerators sub_2464FC@0x2464FC (libanogs), sub_599B2 (0x295 '/proc/self/maps'), and sub_1FB6C@0x1FB6C (libanort basename table) are NAME-FED — they look up a specific target module rather than diffing the whole map for unknowns. GUESS: presence alone does not flag us; our lib is only enumerated if a caller passes its name or a CRC range happens to cover it. Confirm the fed names (open question #1).


## Build spec — what our .so / smali build MUST and MUST-NOT do

- DO-NOT inline-hook (.text/Dobby) ANY scanned module — libil2cpp, libc, or ACE libs. Caught by libanogs sub_17A590@0x17A590 (memcmp vs on-disk file) + sub_2E7DF0@0x2E7DF0 (r-xp RWX CRC) + primitive sub_34EE46@0x34EE46 (byte-exact, zero tolerance), and libanort sub_F368E@0xF368E (.text md5_crc32). Use GOT/PLT redirection or a trampoline in a fresh anonymous page outside the scanned r-xp range instead.

- DO-NOT byte-patch any libanogs scanner body (sub_231B44@0x231B44, sub_23267C@0x23267C, sub_2E7DF0@0x2E7DF0) — they are themselves inside ACE's .text integrity-scan scope, so patching them trips sub_17A590/sub_2E7DF0. And DO-NOT byte-patch libanort .text at all: rolling-checksum VM sub_E24BC@0xE24BC (561 call-sites) and self-kill stub sub_ED584@0xED584 (kill(getpid(),9) if checksum != -886961982) punish any change.

- DO-NOT NOP libanort's exit_group SVC sites (raw bytes f827 00df @0xd6fc, 108 of 114 sites are R7=0xF8=248). Blanket-patching them self-DoSes ACE's own syscalls (the exported gateway tp_syscall_imp@0x108AF0 takes a dynamic syscall nr) and trips the sub_E24BC@0xE24BC VM checksum. Kill detection upstream, never the kill sink.

- DO-NOT rely on LSPatch --sigbypass alone for the cert. libanort sub_851D8@0x851D8 parses 'APK Sig Block 42' natively from the APK-on-disk, below the Java PackageManager layer that sigbypass patches. The cert must be made benign at the file/read level, not just the Java layer.

- DO-NOT expect a runtime memory patch to hide the modified base.apk. libanogs sub_231B44@0x231B44 and libanort sub_5B87C@0x5B87C hash the on-disk FILE (read via sub_35CF60@0x35CF60, lseek sub_35CFAC), so ground truth is the file, not memory. Defense must be file-level (feed pristine bytes to the read) or upstream neuter.

- DO-NOT break ACE init_info. Worker sub_DBC9C@0xDBC9C validates init_info (size==12, game_id at +4) and SIGKILLs via kill(getpid(),9) at 0xDC146 on the failure branch; AnoSDKInit@0xE6E04 is FF's boot gateway (a full NOP froze boot per STATUS.md). Any init neuter MUST keep init_info structurally valid.

- DO statically neuter the AnoSDKInit@0xE6E04 / AnoSDKInitEx@0xE70B8 ARMING path (the engine-arm, not the whole function) so dispatcher sub_23267C@0x23267C never schedules the CRC opcodes and monitor spawner sub_36570C@0x36570C never spawns the scanner threads. This is the single upstream cut for the entire libanogs feature engine (surfaces a+b+d all flow through it). Must be reconciled with the must-stay-alive init_info validation above.

- DO keep the injected lib name off ACE's tables — libmedia_codec.so is absent from the libanogs name blocklist @0xC5324 (0 grep hits) and not present in the libanort sub_1FB6C@0x1FB6C basename table. Never rename it onto a watched name; this is the one surface already covered by construction.

- DO treat libanort as an INDEPENDENT pipeline that neutering libanogs does not silence. Its aggregator sub_58970@0x58970 is dispatched via the off_11E734 fn-ptr table (0 code xrefs) and drives sub_5B87C; its own report sink is sub_60D86@0x60D86; its terminal kill is exit_group in sub_D5F8@0xD5F8 gated on decoded flag 'enable_gp7_exit_group' (0x2EEF). Address libanort separately.

- DO plan for the server-side ban path, not just the local kill. libanort sub_B6CDC@0xB6CDC formats 'reason:%08x,module:%08x' and uploads via sub_1090E4/sub_1091BC to gamesafe URLs (anort_enable_tcj_upload); libanogs verdicts leave via the GAME callback init_info+8 (tss_sdk_send_data_to_svr), NOT an ACE-owned socket. So blackholing ACE CDN endpoints (dl.listdl.com, down.anticheatexpert.com) is useless — only staying undetected works. (HYPOTHESIS: blob-flip of enable_gp7_exit_group@0x2EEF at file 0x1232AA in the 3rd PT_LOAD, RW flags=6, same-size, survives the .text scan — needs a device test to confirm it also suppresses upload.)


## MUST-STAY-ALIVE (touch these = broken boot or self-kill)

- AnoSDKInit@0xE6E04 (libanogs) — FF's init gateway; a full NOP froze FF boot (STATUS.md, agent a10v). Neuter only the engine-arm path, keep the function returning cleanly.

- sub_DBC9C@0xDBC9C (libanogs) init worker + a well-formed init_info (size==12, correct game_id at +4, tss cb at +8, monitor cb at +12) — else the state machine reaches kill(getpid(),9) at 0xDC146 (SIGKILL). Feed valid init_info; do NOT patch the validation.

- sub_DD960@0xDD960 (libanogs) — thin trampoline that forwards init_info to sub_DBC9C; leave alive, it is not a detector.

- libanort exit_group SVC bytes (0xd6fc and 107 other R7=0xF8 sites), the sub_E24BC@0xE24BC decoder/checksum VM, and exported gateway tp_syscall_imp@0x108AF0 — touching any self-DoSes ACE and trips the rolling-checksum self-destruct. Leave libanort .text byte-identical.

- libanogs scanner bodies sub_231B44@0x231B44, sub_23267C@0x23267C, sub_2E7DF0@0x2E7DF0 and libanort sub_5B87C@0x5B87C / sub_ED584@0xED584 — all inside .text integrity/self-kill scope; neutralize by upstream init-neuter, never by in-place patching.


## Open questions (exact next ida_snap command each)

- Does any scan actually enumerate our EXTRA libmedia_codec.so, or only named targets? sub_2464FC/sub_1FB6C/sub_599B2 are name-fed. NEXT: cmd //c "analysis\tools\ida_snap.cmd <snap> libanogs args RAW\o.json 0x2464FC 3" (inspect arg4=module name) and cmd //c "analysis\tools\ida_snap.cmd <snap> libanogs search RAW\c.json callers 0x2E7978" to list which module NAMES callers pass to the .text-CRC factory.

- Can AnoSDKInit be neutered WITHOUT hitting the init_info-validation SIGKILL at 0xDC146 (prior full NOP froze boot)? NEXT: cmd //c "analysis\tools\ida_snap.cmd <snap> libanogs decompile RAW\init.txt 0xE6E04,0xDD960,0xDBC9C" — identify the single instruction that ARMS the engine (dispatcher/spawner enable) vs the one that sets the ready flag *unk_3D2064=1, to find the minimal safe edit.

- Is libanort's file-scan pipeline reachable independently of libanogs init? Aggregator sub_58970 dispatches via off_11E734 (0 code xrefs). NEXT: cmd //c "analysis\tools\ida_snap.cmd <snap> libanort search RAW\t.json callers off_11E734" (or imm 0x11E734) to find who populates/invokes the table, i.e. whether a libanogs neuter leaves libanort live.

- Does the native APK-Sig-Block-42 parser sub_851D8 read the FILE or a PMS/JNI-fed buffer (decides whether a file interposer defeats it)? NEXT: cmd //c "analysis\tools\ida_snap.cmd <snap> libanort args RAW\a.json 0x851D8" then decompile 0x851D8 to trace the source of its input buffer.

- Does flipping enable_gp7_exit_group (0x2EEF) to 0 in the cipher blob (file 0x1232AA) suppress ONLY the local exit_group in sub_D5F8, or also the sub_B6CDC gamesafe upload? NEXT: cmd //c "analysis\tools\ida_snap.cmd <snap> libanort decompile RAW\d5f8.txt 0xD5F8,0xB6CDC" to check whether report-submit is gated on the same flag, then a device runtime test.


---

## Full catalog
## 1. SIGNATURE / CERT / APK-TAMPER — the decisive detector  [US]

*This is what bans our re-signed, repacked build. Two independent libs read it. Highest priority.*

The modified `base.apk` file hash and the CN=Debug cert are read by **libanogs AND libanort**, client-side (imports.json proves `openat/mmap/fstat/dlopen/dladdr` present — not server-only), and bundled into the report field `cert_md5=%s|apk_hash_1|apk_hash_2|txt_seg_crc` (obfuscated, decoded_strings.txt:1775, ~0x5F5C9).

### libanogs — APK-hash / cert via mapped-segment CRC
| Offset (RVA) | Symbol / our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0x23267C | file-feature dispatcher | Thumb | switch on a1[10]; opcodes 3/0x18/0x1A/0x1B all BL the CRC routine; gated `if(a1[20]==0)` | a1v decompile RAW\orch.txt; search callers 0x231B44 (4 sites, all func_ea=0x23267C) |
| 0x231B44 | apk/module CRC | Thumb | maps a module segment (a1[14]+base, len a1[15]), CRCs it; algo picked by remote flag `use_lf_aphash2` | a1v decompile RAW\aphash.txt |
| 0x246374 | module-base resolver | Thumb | dlopen(RTLD_NOLOAD)+dlsym+dladdr; falls back to maps scanner on miss | a1v decompile RAW\filevar.txt |
| 0x2464FC | /proc/self/maps enumerator | Thumb | XOR-0x18 literals decode to '/proc/self/maps','/proc/%d/maps','r-xp','r--p'; locates a NAMED module | a1v decompile RAW\readers.txt + XOR-0x18 decode |
| 0x30F820 | base.apk path resolver | ARM | parses /proc/%d/maps '.apk' line -> /data/app/%s-%d/base.apk (input to the hash) | a3v decompile RAW\maps_cands.txt |
| 0x5F4DA | `CertMD5` (plaintext) | string | JNI recv-signature path `CertMD5=%s|CertAuthorB64=%s|` fed via export AnoSDKOnRecvSignature->sub_E0D0C@0xE0D0C | strings.json; a1v decompile RAW\onrecv.txt |
| 0xC5324 | loaded-lib name BLOCKLIST | string | frida/substrate/xposed/sandhook/hookzz/whale/epic/xhook — libmedia_codec ABSENT (0 hits) | grep decoded_strings.txt |

```c
// dispatcher sub_23267C @ 0x23267C (trimmed) — all 4 CRC calls live here
if (a1[20] == 0) {
    switch (a1[10]) {
    case 3: case 0x18: case 0x1A: case 0x1B:
        sub_231B44(a1, ..., a4, a5);  // a4/a5 pick maps-vs-file + hash variant
    }
}
```

**Two distinct cert paths — do not conflate:** (1) local self-computed `cert_md5` from the mmap CRC (obfuscated, harder, primary target); (2) JNI `CertMD5` fed the game-supplied signature via `AnoSDKOnRecvSignature`. Our CN=Debug cert is caught by BOTH.

### libanort — file checksum + native APK Sig Block 42 (independent)
| Offset (RVA) | Symbol / our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0x58970 | detection aggregator | Thumb | NO code xref — dispatched via off_11E734 fn-ptr table; runs the file scanner + others | a7v decompile RAW\dec_58970.txt |
| 0x5B87C | file-integrity scanner | Thumb | fopen+fread a target file, checksum via sub_EA634, format %08x, write code 58 -> report sink | a7v decompile RAW\dec_fopen.txt |
| 0x5C458 | base.apk path decode | Thumb | decodes 0x99E 'base.apk','base.odex.apk','%s/data/app/%s-%08x/base.apk' | a8v decompile RAW\c3.txt; grep decoded_strings.txt |
| 0x851D8 | APK Sig Block parser | Thumb | decodes 0x1AFB 'APK Sig Block 42'; parses v2 signing block NATIVELY from APK-on-disk | a8v decompile RAW\sig.txt; grep decoded_strings.txt |
| 0xEA634 | checksum primitive | — | shared checksum used by file scanner + self-kill stub | referenced by 0x5B87C, 0xED584 |

**Critical:** sub_851D8 defeats LSPatch `--sigbypass` — sigbypass only patches the Java PackageManager check; this native parser reads the v2 block straight off the APK.

**Avoid (cheapest first, PROVEN detectors so runtime evasion after-the-fact fails):**
1. Upstream: neuter AnoSDKInit arming so neither lib's scanner runs (see §4 for the must-stay-alive constraint).
2. File-level: feed the file-read paths (0x5B87C, 0x231B44, 0x851D8) Garena's pristine `base.apk` bytes via an open/read interposer while running the patched app. HYPOTHESIS — needs the read source confirmed (open q #4).
3. Runtime memory-patch is USELESS: sub_35CF60@0x35CF60 re-reads the on-disk file.

---

## 2. REPORT + KILL CHAIN — how a detection becomes a ban/death  [US]

Each lib has its OWN verdict pipeline. Silencing libanogs does not silence libanort.

### libanogs — COREREPORT builder + game-drained uplink
| Offset (RVA) | Symbol / our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0x3653D4 | COREREPORT packer | Thumb | serializes 'monitor'/'TSS' detections; gated by BSS byte unk_3DB1EC (if 0 returns 0); self-disables after 3 fails | a2v/a9v decompile RAW\builder.txt |
| 0x365540 | report submit/flush | Thumb | re-looks-up COREREPORT channel (49902), vtbl+20 send; all 5 packer callers gate on sub_3653D4()!=0 | a2v search RAW\c_submit.json callers |
| 0xE8B4A | AnoSDKGetReportData (export) | Thumb | game-side poll; drains queue via sub_36570C -> builder | a9v search rep_callers.json |
| 0x37C15C | ChkInit logger | Thumb | reads init_info+8 = game callback `tss_sdk_send_data_to_svr` — verdicts leave via the GAME, not an ACE socket | a9v decompile RAW\logger.txt |
| 0x24BC4C | hook-error dispatcher | ARM | codes 10/11/14 -> set_inline_hook_error / inline_hook_opcode_dismatch / download_data_failed | a4v decompile RAW\integ2.txt |
| 0x24B8FC | reporter | ARM | formats name=%s|desc=%s, calls loc_D99B0(56,buf) — shared MRPCS queue (~50 sites) | a4v decompile RAW\rep.txt; search d99.json |
| 0x133F6C | tamper-abort thunk | Thumb | __noreturn MOV PC,R2 (R2=1/3) -> SIGSEGV; 497 xrefs; packer fallback when unk_3DB1ED==0 | a2v m2_c_133F6C.txt |

**Uplink insight:** the report leaves the device through FF's own callback `init_info+8`, invoked by game code — NOT an ACE-owned socket. So blackholing ACE CDN endpoints (dl.listdl.com, down.anticheatexpert.com, gamesafe/mobile) cannot stop verdict delivery. Only staying undetected works.

### libanort — own sink + local kill + server upload
| Offset (RVA) | Symbol / our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0x60D86 | report sink | Thumb | malloc 0x400 + __vsnprintf_chk; fed by 8 sites / 7 scanners | a7v search h_60d86.json |
| 0xB6CDC | report builder + upload | Thumb | formats 'reason:%08x,module:%08x'; submits via sub_1090E4/sub_1091BC to gamesafe URLs (anort_enable_tcj_upload) | a8v decompile RAW\report.txt; grep decoded_strings.txt |
| 0xD5F8 | terminal exit_group | Thumb | decodes 0x2EEF 'enable_gp7_exit_group' immediately before linux_eabi_syscall(__NR_exit_group=248) | a8v decompile RAW\d5f8.txt; smoke_svc.json |
| 0xED584 | self-kill anti-tamper | Thumb | mmap RWX, XOR-decode(key 0x1D), checksum; kill(getpid(),9) if != -886961982; then mprotect R-X | a7v decompile RAW\dec_mprotect.txt |
| 0xE24BC | decoder VM / anti-tamper | Thumb | XOR decoder, rolling checksum, self-exit_group on tamper; 561 call-sites; hosts 100/108 exit_group SVCs | a6v/a8v decompile RAW\gates.txt; search cE24BC.json |
| 0x108AF0 | tp_syscall_imp (export) | ARM | generic raw-syscall gateway (a1=nr, dynamic R7) — uncatchable kill/ptrace path | a6v decompile RAW\kill.txt |
| 0xd6fc | inline exit_group site | Thumb | raw bytes `f827 00df` = MOVS R7,#0xF8; SVC #0; 108 of 114 SVC sites | a6v search svc.json + byte read |

**Server-ban even if local kill suppressed:** sub_B6CDC uploads the verdict for a delayed server-side ban. Suppressing the local exit_group alone is insufficient.

**Avoid:** upstream neuter (no scan -> no record -> nothing reaches sink). Do NOT patch sink/submit (downstream, shared, and inside checksum scope). Do NOT NOP exit_group SVCs (self-DoS + VM trip). Blob-flip of enable_gp7_exit_group@0x2EEF (file 0x1232AA, 3rd PT_LOAD RW flags=6, same-size, survives .text scan) is a HYPOTHESIS for the local kill only — confirm it also gates the upload (open q #5).

---

## 3. .text INTEGRITY / HOOK SCANNING — the footprint our .so must not create  [US if we inline-hook]

Our extra lib in maps is LOW risk (§0/§4); the real technique-risk is **inline .text hooks**. PROVEN detectors in both libs:

| Offset (RVA) | Symbol / our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0x17A590 | code-integrity scanner | Thumb | memcmp live exec pages vs bytes read FRESH from the on-disk file, in a1[76]-sized chunks | a4v decompile RAW\a590.txt |
| 0x34EE46 | memcmp primitive | Thumb | byte-exact; one differing byte -> nonzero -> mismatch branch (zero tolerance) | a4v decompile RAW\cmp.txt |
| 0x35CF60 | file read side | Thumb | read/_read_chk (svc when unk_3DB13C&2) — ground truth is the FILE, not memory | a4v decompile RAW\rd.txt |
| 0x378E6C | mismatch recorder | Thumb | walks diff list, counts patched regions, logs '!skip:0x%08x, bin_patch_cnt:%d' | a4v decompile RAW\integ.txt |
| 0x377C1C | diff collector | Thumb | appends {addr,len,val} triples for regions in [base,base+size) | a4v decompile RAW\scan.txt |
| 0x19FCAC | 2nd recorder entry | Thumb | SERVER-RULE-driven call into sub_378E6C with attacker-chosen [base,size] | a4v decompile RAW\fcac.txt |
| 0x2E7F64 | r-xp range locator | ARM | reads /proc/self/maps, matches NAMED module, picks r-xp seg via perm[3]!='x' | a3v decompile RAW\maps3.txt |
| 0x2E7DF0 | .text CRC verdict | ARM | mprotects located range RWX(7), CRCs via sub_394EEC | a3v decompile RAW\verdict.txt |
| 0x2E7978 | per-name CRC factory | ARM | cached-by-name; sole caller of 0x2E7DF0 -> target is arbitrary, not a whitelist | a3v decompile RAW\seg.txt; search v2.json |
| 0x1561F8 | libc-pointer enumerator | Thumb | table of open/read/write/ptrace/kill/dlopen/mmap/fork/syscall/connect... checked via sub_1564AE | a2v kill_report.c |
| 0xF368E | ELF .text md5_crc32 (anort) | Thumb | walks ELF32 section headers, reports module_base|...|md5_crc32|begin|end | a8v decompile RAW\f368e.txt |
| 0xFADFC | libil2cpp target (anort) | Thumb | decodes 'SOBASE_libil2cpp.so' — resolves the exact lib our cheat hooks | a8v decompile RAW\il2.txt |

**Two independent facts make inline hooks fatal:** (1) the compare re-reads the on-disk FILE, so a memory-only patch can't hide; (2) sub_19FCAC lets a server-pushed rule aim the .text diff at any [base,size] at any time, so neutering one built-in scan site is insufficient.

**Avoid:** never inline-hook a scanned module (libil2cpp, libc, ACE libs). Use GOT/PLT redirection or a trampoline in a fresh anonymous page outside the r-xp range. libmedia_codec.so itself: keep file==memory (no self-modifying .text).

---

## 4. WHAT ACE NEEDS TO BOOT — do NOT break these  (safety rail)

The whole libanogs feature engine (§1–§3 scanners) is armed by AnoSDKInit and spawned by the monitor dispatcher — so the clean, single upstream cut is to neuter the ARMING, not each scanner. But a full NOP froze FF boot (STATUS.md), because init is load-bearing and self-validates.

| Offset (RVA) | Symbol / our-name | ISA | Role | Evidence |
|---|---|---|---|---|
| 0xE6E04 | AnoSDKInit | Thumb | FF init gateway: sub_DD960 then sub_36570C(a1>-1,0). MUST-STAY-ALIVE | a10v decompile RAW\anosdkinit.txt |
| 0xE70B8 | AnoSDKInitEx | Thumb | second init entry -> sub_DDF34 -> kill path; neuter symmetrically | a2v search c_kill.json |
| 0xDD960 | init trampoline | Thumb | forwards init_info to worker; leave alive | a10v decompile RAW\chain.txt |
| 0xDBC9C | init worker | Thumb | validates init_info (size==12, game_id+4, tss cb+8, monitor cb+12); sets ready *unk_3D2064=1 | a10v decompile RAW\dbc9c.txt |
| 0xDC146 | init SIGKILL | Thumb | kill(getpid(),9) on init_info validation-failure branch | a10v search killers.json |
| 0x36570C | monitor spawner | Thumb | spawns probe threads via sub_3653D4('monitor',...) cases 0..6 — the TRUE origin of the scanners | a10v decompile RAW\r2.txt |

```c
// init worker sub_DBC9C @ 0xDBC9C (trimmed) — the boot gate + the kill
if (*init_info != 12) { ... kill(getpid(), 9); }   // 0xDC146 on failure
*unk_3D2064 = 1;                                    // ready flag FF waits on
```

**Rules:**
- Keep AnoSDKInit@0xE6E04 returning cleanly and feed a well-formed init_info (size==12, correct game_id) — else SIGKILL at 0xDC146.
- Neuter only the engine-arm / monitor-spawn (sub_36570C), NOT the whole function; identify the minimal arming instruction before editing (open q #2).
- libanort is a SEPARATE pipeline (aggregator sub_58970 via off_11E734) — a libanogs neuter does not silence it; handle it independently (open q #3).
- The extra libmedia_codec.so in maps is LOW risk: the name blocklist @0xC5324 misses it (0 hits) and the maps enumerators are name-fed. Keep the name off ACE's tables and confirm which names callers pass (open q #1).