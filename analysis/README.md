# ACE Own-Analysis Workspace — READ FIRST

**Goal:** build our OWN, ground-truth reverse-engineering corpus of Free Fire OB54's REAL
v7a ACE libraries — `libanogs.so`, `libanort.so` — in the exact detailed style of
`INFO/ace_anticheat_notes/`, but for OUR binaries, not msantiagodev's arm64/UE4 build.

**Why this exists:** every prior attempt reused offsets/logic from
`INFO/ace_anticheat_notes/` (a mirror of msantiagodev/ACE-ANTICHEAT). That repo is
**arm64 + UE4 (Division Resurgence)** by its own README — WRONG ISA, WRONG game. Its
offsets never mapped; we banned every time. We stop borrowing. We analyze the bytes we
actually ship. Proven already: their `libmain.so` claim is wrong — in OUR build
`libmain.so` is Unity's JNI loader, not ACE (see `libmain/notes/`).

**Ground-truth identity** (do not analyze any other copy): each lib's md5/size is in
`analysis/<lib>/IDENTITY.txt`, extracted from `artifacts/split_v7a.apk`
(FF OB54 v1.126.1, versionCode 2019120776).

---

## The two-speed architecture (why it's fast + cheap)

```
HEAVY, ONCE per lib (background, minutes)     LIGHT, fanned to N agents (fast, parallel)
────────────────────────────────────────     ──────────────────────────────────────────
build <lib>.i64  + dump inventory JSON    →   agents READ json + request TINY decompiles
bulk-decompile every function to RAW/         + WRITE their own notes/<NN>_*.md
(analysis/<lib>/RAW/*)                         (never re-run heavy IDA analysis)
```

- The `.i64` database is built ONCE. All later queries reuse it and return in ~2s.
- Agents almost never touch IDA directly — they grep the JSON + the decompiled `.c` corpus
  in `RAW/decomp/`. They only call `ida.sh decompile`/`args`/`search` for a specific
  question the corpus can't answer. This keeps every agent's context tiny.
- **Never** stream a whole IDB or a 100-function listing into the model. Files only.

---

## Directory layout (folder discipline — each lib self-contained)

```
analysis/
  README.md                 ← this file (how the whole thing works)
  ORCHESTRATION.md          ← how the main agent launches the N sub-agents + mission split
  PLAYBOOK.md               ← the exact per-mission recipe every sub-agent follows
  NOTE_STYLE.md             ← the required .md output format (mirrors INFO/ace_anticheat_notes)
  tools/                    ← the IDA automation (driven only via ida.sh)
    ida.sh                    single entry point (batch idat, .i64 reuse, TVHEADLESS)
    ida_inventory.py          ONE-TIME bulk JSON dump (funcs/strings/xrefs/imports/exports/init)
    ida_bulk_decompile.py     ONE-TIME Haruspex decompile-every-function
    ida_decompile.py          on-demand: names/addrs -> pseudocode (+callees/xrefs)
    ida_decoder_args.py       string-decoder arg recovery (call_site -> string_id)
    ida_search.py             svc | imm | bytes | str | callers
  libanogs/
    libanogs.so  IDENTITY.txt  libanogs.i64(after 1st run)
    RAW/         ← all machine output (JSON, decomp/, logs) — gitignored, large
    notes/       ← the human-readable .md findings the agents WRITE  ← THE DELIVERABLE
  libanort/  (same shape)
  libmain/   (done — proven to be Unity, not ACE)
```

---

## Quick start (main agent)

**WINDOWS NOTE:** there is no bash/WSL on this machine — use `analysis\tools\ida.cmd`
(same CLI, calls idat.exe directly; tested working). Historical docs below may say
`ida.sh`; `ida.cmd` is the operative wrapper now. The Phase-1 corpus build is ALREADY DONE
for both libs (.i64 + JSON + detectors exist) — do not re-run inventory/bulk.

1. Build the corpus (background — see `ORCHESTRATION.md` for the exact backgrounded calls):
   ```
   bash analysis/tools/ida.sh libanogs inventory   # builds .i64 + JSON  (minutes, first time)
   bash analysis/tools/ida.sh libanogs bulk         # decompile-all       (slow)
   bash analysis/tools/ida.sh libanort inventory
   bash analysis/tools/ida.sh libanort bulk
   ```
2. When JSON + `RAW/decomp/` exist, launch the sub-agents per `ORCHESTRATION.md`.
3. Each sub-agent follows `PLAYBOOK.md` for its mission and writes `notes/NN_*.md` in the
   `NOTE_STYLE.md` format.
4. Main agent reviews notes, cross-checks against `INFO/ace_anticheat_notes/` (as a HINT
   map only — verify every claim against OUR bytes), updates `STATUS.md`.

## Hard rules for every agent working here
- OUR bytes are truth. `INFO/ace_anticheat_notes/` is a hint map; every number you cite
  must be verified in OUR `.i64`/JSON. If they differ, OUR bytes win — note the divergence.
- Cite evidence: every claim → a function ea / string ea / json file + line. No hand-waving.
- Files not context: dump to RAW/, read selectively. Never paste a whole decompile dump
  into chat.
- One writer per file: an agent owns its `notes/NN_*.md`. No two agents edit the same note.

---

## Exposed panels / examples of the fake stuff they sell

this section is about the panels people actually sell for ff right now and why they are
basically a scam plus a ban magnet. we took one apart completely so you can see the pattern
and recognize it next time someone dms you a "panel".

### example 1: proxy TEAM (com.Sx2.Team.Ban)

full breakdown with every file, decrypted string, server url and the payloads lives in
`teamproxy/README_FINDINGS.md` plus the raw evidence in `teamproxy/` (apk, runtime data
pull, the 3 server .so files still encrypted, the decrypted smali, the ghidra decompile of
his native lib, the xor key, the decrypt scripts). the apk itself is gitignored (41mb) but
it sits in `teamproxy/base.apk` on disk if you want to poke it.

who he is:
- package com.Sx2.Team.Ban, app name "SX2 TEAM PROXY", license server sx2lador.online,
  telegram t.me/sx2team/3822
- sells "mod panels" for free fire, license keys look like SX2-TEAM-XXXXXXXX
- his app needs shizuku (root shell) and his api needs a device id + his hmac secret
  (Sx2TeamAppSecureKey2026@!) so every install is tied to a device and to your key

what the app actually does (not what the ads say):
1. checks your license key against his server (verify.php, GetKey.php)
2. with shizuku it writes 3 files into the ff data dir:
   - localconfig.json with {"testCodePatch":true,"resetGuest":true} which tells the game
     to load the hotfix patch, a garena test flag
   - Assembly-CSharp-patch.bytes which is a hybridclr hotfix dll injected into the game
   - reporfnew.db
3. the hotfix then downloads an encrypted arm64 .so from his server
   (libXZAXZAXZAXZA.so / libZZZZZZZZZZZZ.so / libQWERTYUIOPAS.so per "mode") and loads it
4. it also cleans up traces (deletes cache_prefs.dat) and hides the lib in ff's own
   msdk_http_cache folder so it blends in

### why these panels can only ever give you esp, never a real aimbot

we fully recovered the hotfix patch he injects, every method call in it. it is esp only.
the full list of what it can do:
- GetHeadTF / GetHipTF / GetAttackableCenterWS on enemy players to get bone positions
- WorldToScreenPoint to project them on your screen
- IsLocalPlayer / IsLocalTeammate / get_CurHP / get_MaxHP so it skips yourself and teammates
- an overlay canvas that draws boxes, head dots, health bars, lines (toggles __ebox,
  __ehead, __efull, __ehp, __eline, __espcv, __m)
- that is literally it

there is zero aim code in it. no eulerAngles writes, no LookAt / LookRotation, no
fire/shoot/trigger control, no target lock, no smoothing, no silent aim. we scanned for
all of it, it is not there. the one set_localRotation in the patch is just the overlay
canvas rotating itself, not your gun.

why that is always the case with these sellers:
- a real aimbot needs to write camera angles or player transforms inside the game process
  every frame. that is the single most detected thing in any anticheat. doing it from a
  shizuku file drop is impossible, the hotfix dll approach is for ui/esp stuff only
- so the seller ships esp (which works and looks impressive in the promo video) and just
  says the aimbot is "coming" or blames your settings. the aimbot in the ad is either a
  replay edit or another game
- if a panel does have real aim it gets detected and burned in days, so they never build it

### and even the esp gets you banned

the esp side is not safe either, here is what it leaves:
- localconfig.json with testCodePatch true is a garena test flag, it is checked and it is
  abnormal on a real account
- the game loads Assembly-CSharp-patch.bytes, ace can hash the loaded assemblies and see
  the patch
- the downloaded .so sits in msdk_http_cache and gets loaded into the game process. ace
  scans loaded libraries and does memory scans, a foreign lib with esp strings in it is a
  ban
- the app phones home with your device id, your key, your package name and a signature
  every time, so the seller keeps a log of who uses the panel and when. if he gets
  pressured or his server leaks, your device id is on the list
- plus reporfnew.db and the shader cache file are known ff cheat markers

so the realistic outcome of buying one of these: you pay, you get walls that maybe work
for a few games, and then the account gets flagged. the seller already has your money and
your device id.

### the obfuscation he used and how we cracked it

for anyone who wants the technical part, the app was protected like this:
- np.protect style shell (assets encrypted in a folder nested 1000 levels deep, the real
  files only appear after the app runs)
- every class and method renamed to chinese poetry fragments (将进酒 lines) so the smali
  is a wall of poem names
- every string encrypted with a layered scheme: base64 of hex, then xor with one giant
  6978 char arabic diacritics key string
- the real logic moved into a native lib123.so that talks back to java through jni
  wrappers, and its own string table in rodata is encrypted with the same scheme

how we broke it, all scripts in teamproxy/analysis_scripts/:
1. pulled the apk and the runtime data dir (root) after the app unpacked itself
2. recovered the static xor key (teamproxy/xor_key.txt)
3. wrote the decryptor for the java layer, dumped every string of the whole app
4. ran ghidra headless on lib123.so, then recovered the native rodata key + cipher pairs
   the same way and decoded all 164 native strings
5. found the real payloads in assets/ALL01.zip, extracted the 4 modes
6. the only thing still encrypted is the server side .so he downloads. we got all 3
   files, tried the key every possible way (ascii, hex, multiple ivs, even inside his own
   app jvm via frida) and it is not the literal key string, he derives it at runtime in
   the hotfix il. full detail in README_FINDINGS section 10 if someone wants to finish it

### the pattern to spot these panels

- asks for a license key tied to your device id, that is how they track you
- needs shizuku or a vpn style "proxy" to drop files, never a real in game module
- the promo shows aimbot but the download only has esp toggles
- files land in the game data dir or msdk cache, that is the giveaway it is a file injector
- the moment it needs your game version + your device id + a key, you are the product
