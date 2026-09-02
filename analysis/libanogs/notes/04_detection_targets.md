# libanogs.so — Detection targets (our v7a analysis)

> Source of truth: OUR analysis/libanogs/libanogs.so (md5 2810a533, from IDENTITY.txt).
> Cross-ref hints (verify, don't trust): INFO/ace_anticheat_notes/03_detection_targets.md,
> 38_detection_inventory.md, 58_virtual_app_signatures.md — arm64 + UE4 build.

## Summary

Inventory of what ACE v7.7.50.28931 (our armv7 build) *searches for* and *reports*, from the
plaintext string table (`strings.json`, 8896 strings) + the pre-run hunt (`detectors.json`).
Most detection strings are **encrypted** (agent A3's decoder / `decoded_strings.txt` did not
exist yet at analysis time) — plaintext covers report-field names, not the scan target lists
(frida/xposed/root-path tables are invisible until M3 lands). The cert question (STATUS.md
H-A..H-D) is **partially answered** — see the cert section; the decisive finding is that
libanogs has a dedicated export where the *game hands it the signature*, plus a native
APK-file hash path. 16 detection rows logged via `hist.py add-detection`.

## Evidence

### 1. Signature / cert (CRITICAL — affects-us)

| Offset (RVA) | Name / string | ISA | What it is | Evidence |
|---|---|---|---|---|
| 0xEC996 | `AnoSDKOnRecvSignature` (export) | Thumb | The game hands ACE the APK signing cert | exports.json; decompile (this session) |
| 0xE0D0C | `sub_E0D0C` | Thumb | forwards it into the core command dispatcher, cmd **34** | decompile: only callee is `loc_D99B0` |
| 0xD99B0 | `loc_D99B0` | Thumb | core opcode dispatcher (also cmds 10/18/45/-26 seen) | callees of sub_DC804 / sub_E0D0C |
| 0x5F4DA | `"CertMD5"` | — | cert-MD5 report field name | strings.json; ref from **unanalyzed code at 0x39E25C** |
| 0x5F1EF/0x5F61C/0x5FD8D | `"apk_path:%s"` `"apk_path"` `"apk_path=%s"` | — | the installed APK path is collected + reported | strings.json; refs 0x19ADB0..0x19AFDC (unanalyzed region) |
| 0x231B44 | `sub_231B44` | Thumb | maps a file (a1[11]=size), computes a hash of it — the **APK hash** path | decompile (below) |
| 0x64DEB | `"use_lf_aphash2"` | — | remote-config switch selecting the hash routine, **default 1 (ON)** | decompile sub_231B44: `sub_245730("use_lf_aphash2", 1)` |
| 0x61621 | `"ScanCast"` | — | scan component named in the same unanalyzed region as `CertMD5` | strings.json; ref 0x39E254 |
| 0x3A6EA8 | `"com.dts.freefireth"` | — | our package name hardcoded, 0 xrefs (referenced only via encoded path) | strings.json |

```c
// sub_231B44 @ 0x231B44 (trimmed) — APK file hash, remote-config-gated
if ( a1[11] != 0 ) {                       // file size known
    v5 = sub_245E24();                     // open/map the file
    v11 = v12 ? sub_246374(...) : sub_2464FC(v5,&v16,-1,a1[11],0);
    if ( v11 && v16 != 0 ) {
        if ( a5 & 1 ) *a2 = sub_20C998(v16 + a1[14], a1[15]);
        else {
            if ( sub_245730("use_lf_aphash2", 1) != 0 )       // remote config, default ON
                 *a2 = sub_209A88(v16 + a1[14], a1[15], 5);   // hash v2
            else *a2 = sub_2043B0(v16 + a1[14], a1[15]);      // hash v1
        }
    }
}
```

`AnoSDKOnRecvSignature` wrapper itself is anti-tamper-obfuscated (constant-folding state
machine: `((v5 ^ *v22) + (v5 | ~*v22) + *v22 + 1) ^ (v5 | *v22) == 0`), then tail-calls
`sub_E0D0C(...)`. `sub_E0D0C` validates its 3 args (non-null pointers/len) and issues
`loc_D99B0(34, ctx, 0, 0, 0)` — opcode 34 = "process received signature" — plus a second
`loc_D99B0(-26, ctx, 0, 49, 0)` call. **`AnoSDKOnRecvSignature` has xrefs_to=0** — it is
resolved via the export-name string `0x1E4B` referenced at 0x10C0 (export-table region),
i.e. the *game's* Java/JNI code calls it. `search callers sub_E0D0C` → `[]` (its 2 xrefs
are data/table references).

### 2. What the plaintext table actually shows (scan-adjacent fields)

| String ea | String | Referenced from | Meaning |
|---|---|---|---|
| 0x66283 | `name=%s\|rate=%.2f\|is_root=%d` | `sub_36B8E4` @0x36B8E4 (decompiled) | root-scan verdict report (calls `sub_36B494`) |
| 0x60F77 | `mt2_no_root` | region after `sub_151044` @0x151044 | root-status check inside a generic checker runner |
| 0x64BC9 | `!skip:0x%08x, bin_patch_cnt:%d` | `sub_378E6C` @0x378E6C (decompiled) | **memory bin-patch counter** (integrity of mapped code) |
| 0x64511/0x60969/0x60213/0x65DD5 | `ms_set_inlie_hook` / `set_inline_hook_error` / `inline_hook_opcode_dismatch` / `ms_hook_opcode` | `sub_24BC4C` @0x24BC4C | telemetry of ACE's **own** inline-hook engine |
| 0x5F62F | `%s;crc:%s` | `sub_24BC4C` | file CRC reporting (COREREPORT) |
| 0x63862 / 0x368F5A | `hash_cache` | `sub_368ED4` @0x368ED4 (decompiled) | file-hash cache flush |
| 0x6507D | `\|emulator_name=` | `sub_DC804` @0xDC804 (decompiled) | TDM device-info report builder (opcodes 10/18/45) |
| 0xCED2D | `@^NOX]hvgzaq` | none (decoded at runtime) | obfuscated "NOX" emulator name (GUESS) |
| 0x5FD99 / 0x60C8C | `debugger=%s` / `debugger:%s` | 0x19AEC6 / 0x19AEAE (unanalyzed) | debug-attach report fields; same region as `check_state=%s/%s` (0x61AF7/0x62AEE/0x64D90) and `apk_path` |
| 0x5F278 / 0x5F7D3 | `/data/data/%s/files` / `/data/user/10/%s/files` | `sub_310180` @0x310180, `sub_36D470` @0x36D470 | app-private dir scans incl. work profile (user 10) |
| 0x660D6 | `com.ace.gamesafe4` | 0x175D9E..0x175E30 (unanalyzed) | ACE companion-package self-check |
| 0x5FB4E/0x64F43/0x62D05/0x64F50 | `tdm_report` / `tdm_dev_info` / `COREREPORT` / `e_hbeat` | sub_3653D4, sub_364D30, sub_365298/540 | the report channel + heartbeat |

### 3. Hunt's 14 detector functions (RAW/detectors.json)

Only two groups matter. **Killers:** `sub_1561F8` (calls kill+syscall+ptrace+fork = classic
self-watch anti-debug watchdog), `sub_17B00C`, `sub_35D858`, plus the libc wrappers
`kill`@0x398E80, `syscall`@0x398FC0, `ptrace`@0x398F60, `fork`@0x398FE0. **Reporters:**
sub_364D30/sub_365298/sub_3653D4/sub_365540 (COREREPORT/tdm). The three "vm" hits are C++
runtime strings (`Pure virtual function called!` etc.), NOT virtualization detection —
false positives of the hunt regex.

## How it fires / call graph

```
game Java/JNI ──► AnoSDKOnRecvSignature (0xEC996, export)
                     └► sub_E0D0C (0xE0D0C) ──► loc_D99B0(cmd=34)  [core dispatcher]
native boot/scan ─► sub_231B44 (0x231B44) ─► hash apk bytes (use_lf_aphash2)
scanners ─► sub_151044 (checker runner, reports via sub_106944(55,...))
         ─► sub_378E6C (bin_patch_cnt)
         ─► sub_36B8E4 (is_root verdict)
all verdicts ─► COREREPORT builders (sub_3653D4/sub_365540/sub_364D30) ─► server (M5 scope)
```

## Divergence from the arm64 notes

- 38_detection_inventory.md lists plaintext frida/root/emulator paths (`/data/local/tmp/
  frida-server`, `/init.vbox86.rc`, ...). In OUR v7a libanogs **none of these are
  plaintext** — the scan-target tables live in the encrypted string pool (~2000+ strings,
  M3 pending). Their absence from plaintext is a build difference, not an absence of the
  feature.
- 58_virtual_app_signatures.md's 21-package virtual-app table: not visible in our plaintext
  at all; treat as still-encrypted. Only `com.ace.gamesafe4` (ACE's own package) is plaintext.
- arm64 note says `ACE_VirtualEnvDetector` lives in libanort+0xAB9A4 — our libanort scope
  (A2/A3), not verified here.

## The cert-read answer (STATUS.md H-A/H-B/H-C/H-D)

**PROVEN:** libanogs itself never calls PackageManager/CertificateFactory (no such strings,
and `AnoSDKOnRecvSignature` + `apk_path` collection exist instead). Two client-side paths:
1. **Game hands the signature in** through exported `AnoSDKOnRecvSignature` → cmd 34. This
   matches **H-C-flavored** flow on the *game* side (the game's own Java reads signingInfo
   and passes it over Binder/PackageManager), and is the natural carrier for **H-D**
   (server compares the received cert hash against Garena's known hash for com.dts.freefireth).
2. **ACE natively hashes the installed APK** (`apk_path` + `sub_231B44`, `use_lf_aphash2`,
   default ON) — a boot/file-time read (H-A-like) that no Java PackageManager hook would
   cover.
**NOT visible in libanogs:** any direct `hasSigningCertificate` Java call from libanogs
(H-B as *libanogs* behavior) — cannot rule out libanort or the ACE Java layer.

**Net:** our re-signed build must defeat BOTH the signature passed in by the game (lie at
the `AnoSDKOnRecvSignature` boundary — it is a clean, single JNI choke point) AND the native
APK hash (`use_lf_aphash2` is remote-config-gated; the hash source is a mapped-file read
that could be redirected like any file read). If H-D is true (server-side compare of the
received signature), only feeding a genuine-looking signature through path 1 survives.

## Bypass implications (our build: no framework, one extra .so, re-signed cert)

1. **PROVEN affects-us — re-signed cert:** path 1 (`AnoSDKOnRecvSignature`) is the cheapest
   hook point: one export, four args, returns int. Feeding it the original Garena signature
   blob (captured from a stock install) dodges both the cmd-34 verification and H-D, if the
   blob is what gets compared.
2. **PROVEN affects-us — native APK hash:** `sub_231B44` hashes whatever file `apk_path`
   points at. Same file-redirect we already use (or flipping the `use_lf_aphash2` remote
   config to 0, which downgrades it to the v1 hash) is the lever. Needs runtime test to
   confirm which file object a1 points to (H-Ap: hash of base.apk).
3. **affects-us 0 — everything else:** no framework (xposed/lspatch rows moot), not rooted
   (`is_root`/`mt2_no_root` moot), no debugger, not on an emulator (emulator_name moot),
   we don't patch ACE code (`bin_patch_cnt` stays 0). Our extra `libmedia_codec.so` would
   only matter to a maps/library-name scanner — those name lists are still encrypted (TODO
   below), so treat "unknown .so in maps" as an OPEN HYPOTHESIS, not a proven trip.
4. Report channel (COREREPORT/tdm/e_hbeat) is M5's target — every verdict above funnels
   there; that's where a kill switch pays off once.

## Open questions / next probes

- **Decoded strings (M3):** rerun this inventory against `RAW/decoded_strings.txt` when A3
  publishes it — the frida/xposed/lspatch/npatch/root/emulator target lists and any
  `CertificateFactory`/`getModulus`/`signingInfo`/`META-INF` strings live there. Until then
  they are TODO, not proven absent.
- `analysis\tools\ida.cmd libanogs decompile <out> 0x39E25C` fails ("decompile failed") —
  the `CertMD5`/`ScanCast`/`/data/data` refs sit in an IDA-unanalyzed gap (0x399830–0x3EA2D0,
  ~19 KB after `dl_unwind_find_exidx`). Force-analyze that range (`ida_mark` on 0x39E000
  region or `ida.cmd search bytes` around it) — it is our best remaining native-cert code.
- Same for the 0x19A800–0x19B100 gap (`check_state`/`debugger=`/`apk_path=` cluster) and
  0x175B88–0x175E38 (`com.ace.gamesafe4`).
- Decompile `sub_36B494` (the is_root verdict sink) and `sub_106944` (report sink used by
  the checker runner, arg 55) to bind verdicts to report opcodes — feeds M5.
- Runtime probe from STATUS.md stands: hook `AnoSDKOnRecvSignature` in our probe and log its
  4 args — that directly shows whether the game passes the raw cert bytes or an opaque ID.
