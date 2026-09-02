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
