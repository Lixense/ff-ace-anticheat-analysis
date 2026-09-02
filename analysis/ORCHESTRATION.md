# ORCHESTRATION — how the main agent runs the analysis fleet

## Model note (answering the user's question)
- The main/orchestrator agent = **Opus 4.8 (1M)** — that's me, doing planning + review + the
  heavy IDA builds.
- Sub-agents = **Sonnet** (spawned via the Agent tool with `model: "sonnet"`, which maps to
  your configured Sonnet 5 / `[1m]` in this harness). Fast, cheap, parallel. The literal
  `[1m]` tag can't be typed into the tool; the harness mapping supplies the 1M context.
- **YES**, multiple Sonnet sub-agents run in parallel — launch them in ONE message (multiple
  Agent tool-calls in a single turn) and they execute concurrently.

## The golden rule of parallelism here
**Parallelize AGENTS, serialize IDA _analysis_.**
- Building a `.i64` for a lib is heavy and must happen ONCE per lib (two libs = two builds).
  Never let 5 agents each run `inventory`/`bulk` on the same lib — they'd race the same DB.
- Once `.i64` + JSON exist, many agents querying via `ida.cmd decompile/search`
  is fine: each spins a short-lived idat that opens the DB read-only for ~2s. Cheap.

## Phase 1 — build the corpus (main agent, background, ONCE)
Run these BACKGROUNDED (each takes minutes on first analysis; `libanogs` is 4 MB):
```
# inventory first (builds the .i64 both later steps reuse), then bulk decompile
bash analysis/tools/ida.sh libanogs inventory      # ~several min (4 MB, first analysis)
bash analysis/tools/ida.sh libanort inventory      # ~1-2 min (1.4 MB)
bash analysis/tools/ida.sh libanogs bulk            # decompile-all (longest)
bash analysis/tools/ida.sh libanort bulk
```
Use the Monitor tool or a backgrounded Bash job; watch each `RAW/*.log` for "DONE".
Gate: do NOT launch sub-agents until `summary.json` AND `RAW/decomp/index.tsv` exist for
the target lib.

## Phase 2 — launch the fleet (main agent, ONE message, parallel)
Assign one mission per sub-agent. Recommended split (5 agents, both libs share missions but
`libanogs` is the priority — it holds reports + kill chain):

| Agent | Model | Lib | Mission | Writes |
|---|---|---|---|---|
| A1 | sonnet | libanogs | M1 exports/JNI | notes/01_exports_jni.md |
| A2 | sonnet | libanogs | M2 init flow | notes/02_init_flow.md |
| A3 | sonnet | libanogs | M3 string decryption | notes/03_string_decryption.md + RAW/decoded_strings.txt |
| A4 | sonnet | libanogs | M4 detection targets (esp. CERT) | notes/04_detection_targets.md |
| A5 | sonnet | libanogs | M5 kill chain & report | notes/05_kill_chain.md |

M3 (string decryption) is the keystone — M4 depends on decoded strings. Two options:
- **Sequential-ish:** run A3 first (or give it a head start), then A1/A2/A4/A5. OR
- **Parallel with fallback:** A4 starts from plaintext `strings.json`, then refines once A3
  publishes `decoded_strings.txt`. (A4's note says which strings are still-encrypted TODO.)

Repeat Phase 2 for `libanort` after (or with a second wave of agents) — same missions.

## Sub-agent launch prompt (template)
Each Agent call's prompt MUST contain:
```
You are a RE sub-agent. Read analysis/README.md, analysis/PLAYBOOK.md, analysis/NOTE_STYLE.md.
Your mission: <Mx — name> on <lib>.
Work ONLY from analysis/<lib>/RAW/* and targeted `analysis\tools\ida.cmd <lib> ...` calls
(WINDOWS: no bash here — never `ida.sh`).
Produce analysis/<lib>/notes/<NN_name>.md in NOTE_STYLE format, every claim cited to OUR bytes.
Cross-check (hint only, verify in our bytes) against INFO/ace_anticheat_notes/<file>.
Do NOT run `inventory` or `bulk` (already done). Do NOT edit any other agent's note file.
When done, reply with: the note path + a 5-line summary of key offsets you found.
```

## Phase 3 — review & synthesize (main agent)
- Read each `notes/NN_*.md`. Verify offsets are internally consistent (spot-check one via
  `ida.cmd decompile`).
- Build `analysis/<lib>/notes/00_INDEX.md` linking all notes + a one-line TL;DR each.
- Reconcile with `INFO/ace_anticheat_notes/`: where OUR bytes differ, OUR notes win; record
  the divergence so we never re-trust a stale arm64 number.
- Update `STATUS.md` with what we now KNOW (proven) about OUR ACE, and the shortlist of
  kill switches / cert-read path with real v7a offsets.

## Cost / scale discipline (per the user: "smart fast, not heavy things")
- Sub-agents are Sonnet, read-mostly, short-lived. Each should finish its mission in a
  handful of `ida.cmd` calls + grep. If one balloons, it's doing IDA's job — stop it, tighten
  the mission.
- Keep ≤5 agents in flight at once. Two libs × 5 missions = 10 notes total, in two waves.
