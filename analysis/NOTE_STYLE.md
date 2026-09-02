# NOTE_STYLE — the required output format for every findings .md

Match the style of `INFO/ace_anticheat_notes/` exactly. Those notes are good because they
are: (1) evidence-anchored (every claim has an offset), (2) decompile-backed (real
pseudocode, trimmed), (3) actionable (they end in "bypass implications"). Reproduce that.

## File naming
`analysis/<lib>/notes/NN_topic.md` — NN = zero-padded order (00, 01, ...). One topic per
file. Keep files focused; many small notes beat one mega-note.

## Required skeleton

```markdown
# <lib>.so — <Topic> (our v7a analysis)

> Source of truth: OUR analysis/<lib>/<lib>.so  (md5 <first8>, from IDENTITY.txt).
> Cross-ref hint (verify, don't trust): INFO/ace_anticheat_notes/<file> — arm64 build.

## Summary
2-4 sentences. What this subsystem is and why it matters to the head-lock goal / the ban.

## Evidence
Concrete, addressed findings. Use a table when listing offsets:

| Offset (RVA) | Symbol / our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0x1DA368 | AnoSDKInit | Thumb | public SDK init | exports.json; decomp/AnoSDKInit_1DA368.c |

Inline the RELEVANT pseudocode only (trim to the lines that prove the claim):

```c
// AnoSDKInit @ 0x1DA368  (from decomp/, trimmed)
int AnoSDKInit(int game_id) {
    ...only the decision-relevant lines...
}
```

## How it fires / call graph
Who calls it, what it calls (from the `// callees:` header + `search callers`). Trace the
chain to a concrete effect (a report, a kill, a file read).

## Divergence from the arm64 notes
State explicitly where OUR bytes differ from `INFO/ace_anticheat_notes/`. (Offsets WILL
differ — that's expected. Note if the LOGIC differs too.)

## Bypass implications
What this means for us, cheapest option first. Only claim what the evidence supports.
Distinguish PROVEN (saw it in the bytes) vs HYPOTHESIS (needs a runtime test).

## Open questions / next probes
Exact next `ida.cmd` command or runtime test that would resolve each unknown.
```

## Evidence-citation rules
- Every offset is an **RVA** (file/image offset from IDA, image_base in summary.json is 0).
  When you hand an offset to a runtime patch, note ISA (Thumb=odd address semantics).
- Cite the artifact: `functions.json`, `strings.json`, `decomp/<f>.c`, or the `ida.cmd`
  command you ran. A claim with no citation is a TODO, not a finding.
- Quote decoded strings with their string-id: `decoder(44710) -> "ob_cdn2.zip"`.
- Never invent an offset. If you didn't see it in OUR data, say "not yet located".

## Tone
Terse, technical, honest. No filler. If something is a guess, label it. The reader is
another engineer (or the main agent) who will act on your numbers — wrong numbers = SIGILL.
