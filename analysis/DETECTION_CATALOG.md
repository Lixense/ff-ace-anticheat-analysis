# DETECTION CATALOG — everything ACE checks, and how our SMALI build avoids it

> **This is THE deliverable.** One question drives the whole project: *how does ACE detect
> us, and how do we avoid it with the static-smali-inject method?* This file is the answer,
> kept current from OUR v7a analysis (`analysis/libanogs`, `analysis/libanort`). The live,
> queryable form is `analysis/History/ace.db` (`python analysis/tools/hist.py detections
> --affects-us 1`). This .md is the human-readable master.

> Legend:  **[US]** = our current smali build trips this → must fix.  **[ok]** = doesn't
> apply to a clean smali build (no framework, no root, real package).  **[?]** = unverified.

---

## 0. Why smali-inject already dodges MOST of ACE (the big picture)
Our method = decompile FF's own APK, drop `libmedia_codec.so` into `lib/armeabi-v7a/`,
add ONE `System.loadLibrary("media_codec")` line to `FFApplication.<clinit>`, re-sign.
That means we are `com.dts.freefireth`, real UID, real package, real mount namespace, NO
Xposed/LSPatch/NPatch framework, NO container. So entire ACE tiers are **inert by
construction** — we must only beat the few that a re-signed, one-extra-.so APK still trips.

| ACE tier | Trips our smali build? | Why |
|---|---|---|
| Virtual-app / container (21 engines) | **[ok]** | we're not in a container; real package |
| Root (Magisk/KernelSU/su paths) | **[ok]** | device is non-root |
| Xposed/LSPatch/NPatch framework footprint | **[ok]** | smali-inject ships NONE of it (this was the v1/v2 killer) |
| Emulator | **[ok]*** | *allowed by FF server on BlueStacks; real target is Realme (real device) |
| **Signature / cert / APK tamper** | **[US]** | re-sign → cert ≠ Garena; THE fight |
| **Extra .so in maps** (`libmedia_codec.so`) | **[?]** | one unknown lib in maps — verify ACE's maps scan |
| **.text integrity / RWX** (if we hook) | **[?]** | only if our .so inline-hooks; GOT-mode avoids |

So the catalog below focuses hard on the **[US]** and **[?]** rows. The rest we record for
completeness but do not spend effort on.

---

## 1. SIGNATURE / CERT / APK-TAMPER  — the decisive detector  [US]
*This is what bans our re-signed build. Highest priority. Fill from libanogs analysis.*

Proven so far (our bytes):
- `AnoSDKOnRecvSignature` export @ **libanogs 0xEC996** (Thumb) — heavily obfuscated
  (opaque predicates). Name implies the game feeds ACE a signature and the **server**
  decides (hypothesis H-D). If validation is server-side, no client hook fixes it — we must
  make the value SENT be Garena's. `evidence: exports.json, sig_recv.txt`.
- `CertMD5` string @ **libanogs 0x5F4DA** — ACE computes an MD5 of the cert. Our re-sign
  changes it. `evidence: detectors.json`.
- `AnoSDKOnRecvSignature` also appears as a plaintext string @ 0x1E4B.

TODO (agents M4/M5): find where CertMD5 / the cert bytes are read, whether it's file-read
(`CertificateFactory.generateCertificate`) vs PMS vs server-fed; trace to the report field
(`apk_hash`, `cs`). Record each as a detection row with the exact avoid.

**Avoid options for smali (to be validated):**
1. Keep FF's ORIGINAL signature — impossible without Garena's key.
2. Make ACE read Garena's cert bytes (hide file-read / feed original) — needs the read path.
3. Kill the report that carries the verdict (see §2) — server fail-open on absent report?
4. Server-side attestation (H-D) → may be unwinnable client-side; must confirm first.

---

## 2. REPORT + KILL CHAIN — how a detection becomes a ban/death  [US for report]
*Fill from libanogs (report) + libanort (kill). This is the "silence the verdict" target.*

Proven so far:
- `COREREPORT` channel string @ libanogs 0x62D05 (4 xrefs); `tdm_report` @ 0x5FB4E;
  `tdm_dev_info` @ 0x64F43. The report subsystem is real in our build.
- libanort exports `tp_syscall_imp` @ 0x108AF0 — raw-syscall wrapper (kill chain uses raw
  `svc` to dodge libc hooks). `g_acf_array` @ 0x15DB0C, `g_aco_array` @ 0x15F15C = ACE core
  function/global tables.

TODO: `ida.cmd libanogs search svc` + trace to `exit_group`/`kill`; find the report-enable
flag (the `g_tdm_report_enabled` equivalent — REAL v7a offset, not the arm64 0x57E31C);
find `senddatatosvr`. Record kill switches with offsets + ISA.

---

## 3. FRAMEWORK / HOOK / FILE / MAPS SCANNING — footprint our .so must not trip  [?]
*Mostly [ok] for smali, but our extra .so + any hooks are the [?]. Fill from both libs.*
- Frida/Substrate/SandHook/HookZz strings → [ok] we ship none.
- **Our `libmedia_codec.so` in `/proc/self/maps`** → [?]: does ACE enumerate maps and flag
  unknown libs? Name is innocuous (not on any list) but presence is real. VERIFY.
- If our .so uses Dobby **inline** hooks on the 31 watched libc fns → caught by .text
  compare. Use **GOT/PLT mode**. Record the watch-list from our bytes.

---

## 4. WHAT ACE NEEDS TO BOOT — do NOT break these  (safety rail)
*The AnoSDKInit NOP froze FF's boot (STATUS.md). Record the init deps so we never re-break.*
- libanogs: 21 AnoSDK* exports, 67 init ctors, `JNI_OnLoad` @ 0xEEE94.
- libanort: `JNI_OnLoad` @ 0xD988, 4 init ctors.
- TODO (M2): which init entry is safe to touch vs load-bearing for the resource handshake.

---

## 5. Everything else (record-and-move-on — NOT our focus)
Emulator fingerprints, streaming/recording apps, account-trading pkgs, VPN, antivirus,
crypto internals, telemetry unrelated to tamper. List them in the DB for completeness
(`type=emulator|vm|...`, `affects-us=0`) but spend NO decompile budget here unless one turns
out to gate a [US] path.

---

## How to add to this catalog
Agents: every detection you confirm →
`python analysis/tools/hist.py add-detection --lib .. --type .. --target .. --affects-us .. --avoid ..`
Then reflect the **[US]** ones here (§1-3) with the offset + evidence. Keep §5 in the DB only.
Main agent periodically regenerates the "[US] avoid-list" section from
`hist.py detections --affects-us 1`.
