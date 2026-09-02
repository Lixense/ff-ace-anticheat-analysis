# PLAYBOOK — exact recipe every sub-agent follows

You are a reverse-engineering sub-agent. You own ONE mission (below). You produce
`analysis/<lib>/notes/NN_*.md` in `NOTE_STYLE.md` format, backed by OUR bytes. You work
from the pre-built corpus; you call `ida.cmd` only for targeted questions.

## THE ONE QUESTION (read this before anything)
The entire project has a single purpose: **find out HOW ACE detects US, so our smali-inject
build can AVOID it.** You are NOT writing a general ACE textbook. For every function you
consider decompiling, ask: *"does this help us understand how we're detected, or how to
avoid it?"* If no → SKIP it. We care about, in priority order:
1. **Signature / cert / APK-tamper detection** (this is what bans our re-signed build).
2. **The report + kill chain** (how a detection becomes a ban / a process death).
3. **Framework / hook / file / maps scanning** (what our `.so` + smali footprint must not trip).
4. **What ACE needs to run for FF to boot** (so we never break it like the AnoSDKInit NOP did).
Everything else (crypto internals, unrelated telemetry, vtable trivia) → note its existence
in one line and MOVE ON. Depth only where it touches the four points above.

## RECORD EVERYTHING to the History DB (fast, searchable)
Besides your `.md`, log structured rows so findings are queryable across all agents:
```
# something ACE detects (goes on the smali avoid-list):
python analysis/tools/hist.py add-detection --lib <lib> --type <sigcert|hook|xposed|lspatch|root|emulator|vm|debug|proc|report|file> \
   --target "<the string/class/path>" --string-ea 0x.. --by-func <fn> --by-func-ea 0x.. \
   --decoded <0|1> --affects-us <0|1> --avoid "how our smali build dodges it"
# a reverse-eng finding (offset that matters to detection/kill):
python analysis/tools/hist.py add-finding --lib <lib> --category <kill|report|init|export|jni|scanner|integrity|string> \
   --name <fn> --offset 0x.. --isa <thumb|arm> --affects-us <0|1> --severity <high|med|low> \
   --summary "..." --evidence "<json/decomp/ida.sh cmd>" --mission <Mx> --agent <your id>
```
`hist.py search <kw>`, `hist.py detections --affects-us 1`, `hist.py report` to read back.

## The tools you have (all via one wrapper)

**WINDOWS CLI (this machine): use `ida.cmd`, NOT `ida.sh`.** There is no bash/WSL here —
`ida.sh` will fail. Same CLI, Windows-native:

```
analysis\tools\ida.cmd <lib> hunt                              # detection-only sweep (START HERE)
analysis\tools\ida.cmd <lib> decompile <out.txt> <name_or_ea[,name2,...]>
analysis\tools\ida.cmd <lib> args      <out.json> <decoder_name_or_ea> [argidx]
analysis\tools\ida.cmd <lib> search    <out.json> svc
analysis\tools\ida.cmd <lib> search    <out.json> imm     <value>
analysis\tools\ida.cmd <lib> search    <out.json> bytes   "<hex pattern>"
analysis\tools\ida.cmd <lib> search    <out.json> str     <substr>
analysis\tools\ida.cmd <lib> search    <out.json> callers <name_or_ea>
```
`<lib>` = `libanogs` | `libanort`. Outputs land in `analysis/<lib>/` (short name) or an
absolute path. Every call reuses the prebuilt `.i64` → returns in ~2-7s (MEASURED:
inventory 154s once, hunt 7s, decompile-2-funcs 3s). Never run `inventory`/`bulk`.

**`hunt` is your starting point.** It's already been run — read `RAW/detectors.json`
(detector functions + the detection strings that reference them) and `RAW/detectors.c`
(their pseudocode) FIRST. That's the pre-filtered "what detects us" set. Only reach for
`decompile`/`search`/`args` to go deeper on a specific detector from that set.

NOTE on strings: ACE encrypts most strings (plaintext `hunt` finds only ~17; there are
~2000+ encrypted). So `hunt`'s plaintext list is the tip. M3 (string decryption) expands
it — until M3 lands, work the plaintext + obfuscated-function leads you can see.

## The corpus you read (already produced, no IDA needed)

```
analysis/<lib>/RAW/summary.json      counts + image_base
analysis/<lib>/RAW/functions.json    [{ea,name,size,thumb,xrefs_to,is_export}]
analysis/<lib>/RAW/strings.json      [{ea,len,type,value,xrefs[]}]  ← plaintext strings only
analysis/<lib>/RAW/imports.json      external libc/libdl calls ACE makes
analysis/<lib>/RAW/exports.json      the AnoSDK*/JNI_* API surface
analysis/<lib>/RAW/init_array.json   C++ constructors (boot order)
analysis/<lib>/RAW/segments.json     segment map
analysis/<lib>/RAW/detectors.json    hunt output: detector functions + string hits
analysis/<lib>/RAW/detectors.c       their pseudocode
```
**NOTE: `decomp/` + `index.tsv` do NOT exist** — bulk decompile-everything was replaced by
the detection-first hunt (23,600 functions made bulk too slow). Work from `detectors.json`
+ targeted `ida.cmd decompile` calls instead.

Read them with `grep`/`python -c`, NOT by dumping whole files into context. Examples:
```
# top 30 most-referenced functions (likely core helpers / decoders):
python -c "import json;d=json.load(open('analysis/libanogs/RAW/functions.json'));d.sort(key=lambda x:-x['xrefs_to']);[print(x['xrefs_to'],hex(x['ea']),x['name']) for x in d[:30]]"
# find a string and who uses it:
grep -i "anticheatexpert" analysis/libanogs/RAW/strings.json
# grep the whole decompiled corpus for a concept:
grep -rl "exit_group\|_exit\|tgkill" analysis/libanogs/RAW/decomp/ | head
```

## Standard workflow (every mission)
1. **Orient** — read `summary.json`, skim `exports.json` + `imports.json`. Understand the
   lib's surface before diving.
2. **Locate** — grep `functions.json`/`strings.json`/`decomp/` for your mission's targets.
3. **Confirm** — `ida.cmd decompile` the 2-10 functions that matter; read the pseudocode.
4. **Trace** — `search callers` / read `// callees:` headers to build the call graph to a
   concrete effect.
5. **Decode** if strings are encrypted — `ida.cmd args <decoder>` to map call_site→string_id,
   then (once the XOR algo is known from the decoder pseudocode) reimplement it in Python to
   dump plaintext. See mission M3.
6. **Write** `notes/NN_*.md` in `NOTE_STYLE.md`. Cite every offset. Label PROVEN vs GUESS.
7. **Cross-check** your findings against the `INFO/ace_anticheat_notes/` file named in your
   mission — but only as a hint. Verify in OUR bytes; note divergences.

---

## Missions (the main agent assigns ONE per sub-agent)

### M1 — Exports & JNI surface  → `notes/01_exports_jni.md`
Map every exported function (`AnoSDK*`) and every JNI-registered native method. For each:
name, ea, ISA, arg count/types (from decompile), what it does in one line. Find `JNI_OnLoad`
and the `RegisterNatives` table (grep decomp for `RegisterNatives`); list Java class +
method → native handler. This is the game↔ACE contract.
Hint file: `66_libanogs_jni_native_api.md`, `32_jni_native_methods.md`.

### M2 — Init flow & boot sequence  → `notes/02_init_flow.md`
`init_array.json` in order → decompile each non-trivial ctor → what state each sets up.
Then `JNI_OnLoad` → the init chain it calls. Identify the SINGLE entry that starts detection
(the `AnoSDKInit`/`*core_init*` equivalent). Note what MUST run for FF to boot (breaking it
froze boot before — see STATUS.md).
Hint file: `30_libanogs_init_array.md`, `00_TLDR_FULL_SYSTEM.md` init section.

### M3 — String decryption  → `notes/03_string_decryption.md`
Find the decoder(s): look for a high-xref function taking one int arg that returns a char*
(grep functions.json for high xrefs_to; decompile candidates). Recover the XOR/algorithm
from its pseudocode. Run `ida.cmd args <decoder>` to get all call_site→string_id pairs.
Reimplement the algo in Python → dump ALL plaintext strings to `RAW/decoded_strings.txt`.
This unlocks EVERY other mission (detection targets are encrypted).
Hint file: `01_string_decryption.md` (algo shape), `64_master_string_dictionary.md`.

### M4 — Detection targets  → `notes/04_detection_targets.md`
Using decoded strings (M3) + `strings.json`, inventory WHAT ACE looks for: frida/xposed/
lspatch/npatch class+lib names, root packages, emulator fingerprints, and — CRITICAL for us
— the **signature/cert** detection (`CertificateFactory`, `getModulus`, `isPatch`,
`generateCertificate`). For each, cite the string ea + the function that references it
(xrefs). Flag which ones OUR current build would trip.
Hint file: `03_detection_targets.md`, `38_detection_inventory.md`, `58_virtual_app_signatures.md`.

### M5 — Kill chain & report path  → `notes/05_kill_chain.md`
`ida.cmd search svc` → every raw syscall (find `exit_group`/`kill`/`tgkill` = the uncatchable
kills; R7 number identifies the syscall). Trace backwards (`search callers`) to what triggers
them. Find the report builder/sender chain (grep decomp for the report host string's xref,
`senddatatosvr`, `corereport`). Identify every kill switch (a byte/flag that disables a path)
with its OUR-build offset. THIS is what we must neutralize to survive.
Hint file: `12_complete_kill_path_inventory.md`, `20_tdm_report_chain.md`, `79_heartbeat_integrity_kill.md`.

---

## Efficiency guardrails (do not violate)
- Don't `bulk`-decompile or `inventory` yourself — the main agent already did (heavy, once).
- Don't decompile more than ~15 functions per `decompile` call; ask focused questions.
- Don't paste more than ~40 lines of pseudocode into a note — trim to what proves the claim.
- If a query would return >200 rows, tighten it (grep/filter) before running.
- Stuck on an unknown for >2 probes? Write it under "Open questions" and move on. Don't spin.
