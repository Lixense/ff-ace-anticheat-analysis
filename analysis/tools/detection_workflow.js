export const meta = {
  name: 'ace-detection-hunt',
  description: 'Decompile OUR v7a libanogs/libanort to prove exactly how ACE detects our smali-inject build, then write the avoid-spec',
  phases: [
    { title: 'Sweep', detail: '10 agents, one detection surface each, own IDA snapshot' },
    { title: 'Verify', detail: 'adversarial re-run of each finding in the bytes' },
    { title: 'Synthesize', detail: 'merge verified findings into DETECTION_CATALOG + build spec' },
  ],
}

// ── shared rules every agent must obey ───────────────────────────────────────
const ROOT = 'REPO_ROOT'   // set this to the absolute path of your local checkout before running
const RULES = `
You are a reverse-engineering agent working on OUR OWN v7a Free Fire ACE binaries.
GROUND TRUTH = only our .i64 databases, queried via ida_snap.cmd.

HARD RULES:
1. NEVER read INFO/ace_anticheat_notes/ — those are arm64/UE4 notes for a DIFFERENT build and
   are the source of the false info we are trying to escape. If you cite them, your finding is void.
2. Every claim MUST cite (a) an RVA offset and (b) the exact ida_snap.cmd command that proved it.
   No offset + no command = a TODO, not a finding. Label PROVEN (saw it in bytes) vs GUESS.
3. Use YOUR OWN snapshot id so you never collide with other agents. Your snapid is given below.
   Run from cwd ${ROOT}. Command form (Windows cmd, run via the Bash tool with cmd //c):
     cmd //c "analysis\\tools\\ida_snap.cmd <SNAPID> <lib> hunt"
     cmd //c "analysis\\tools\\ida_snap.cmd <SNAPID> <lib> decompile RAW\\out.txt <name_or_0xEA[,name2,...]>"
     cmd //c "analysis\\tools\\ida_snap.cmd <SNAPID> <lib> search RAW\\o.json <svc|imm|bytes|str|callers> [param]"
     cmd //c "analysis\\tools\\ida_snap.cmd <SNAPID> <lib> args RAW\\o.json <decoder_name_or_ea> [argidx]"
   Outputs land in analysis\\_snap\\<SNAPID>\\RAW\\ . Read them with the Read tool.
   Each ida_snap call takes ~2-7s and reuses your snapshot's copy of the .i64.
4. Read the pre-built corpus WITHOUT idat (fast): analysis/<lib>/RAW/{functions,strings,exports,
   imports,init_array,detectors,summary}.json and analysis/libanogs/RAW/decoded_strings.txt.
   grep / python -c to filter — never dump a whole json into your context.
5. The ban we are fighting: our build ships (a) re-signed cert CN=Debug, (b) modified base.apk
   (file hash differs from Garena), (c) ONE extra lib libmedia_codec.so in /proc/self/maps.
   We also proved Dobby .text hooks trip integrity scanners. Your job: find in OUR bytes the exact
   function that reads YOUR surface and how its verdict becomes a report/kill. That is the deliverable.
6. libanogs decoded strings already exist (analysis/libanogs/RAW/decoded_strings.txt, 3323 lines,
   checksum-proven). libanort strings are NOT decoded yet.

OUTPUT: return a JSON object matching the schema. Keep pseudocode snippets <=25 lines each.
`

const FINDING_SCHEMA = {
  type: 'object',
  required: ['surface', 'lib', 'findings', 'summary'],
  properties: {
    surface: { type: 'string' },
    lib: { type: 'string' },
    summary: { type: 'string', description: '3-5 sentences: what detects our surface and how the verdict travels to a ban/kill' },
    findings: {
      type: 'array',
      items: {
        type: 'object',
        required: ['claim', 'offset', 'isa', 'proof_cmd', 'confidence', 'affects_us'],
        properties: {
          claim: { type: 'string', description: 'one-sentence defect/detection statement' },
          offset: { type: 'string', description: 'RVA e.g. 0xE6E04, or "none" for a string-only finding' },
          isa: { type: 'string', enum: ['thumb', 'arm', 'data', 'string', 'unknown'] },
          proof_cmd: { type: 'string', description: 'the exact ida_snap.cmd command that proves it' },
          evidence: { type: 'string', description: 'trimmed pseudocode / string / json excerpt proving the claim' },
          confidence: { type: 'string', enum: ['PROVEN', 'GUESS'] },
          affects_us: { type: 'boolean', description: 'does our current smali-inject + .so build trip this?' },
          avoid: { type: 'string', description: 'concretely, how our build avoids or neutralizes it' },
        },
      },
    },
  },
}

// ── Phase 1: the 10 sweep missions ───────────────────────────────────────────
const MISSIONS = [
  { id: 'a1', lib: 'libanogs', surface: 'Signature/cert verification path',
    task: `Trace the APK signature check. Start: decompile AnoSDKOnRecvSignature (0xEC996) and its callee sub_E0D0C (0xE0D0C). Find the "CertMD5" string (grep strings.json) and what reads it. Decompile sub_231B44 (the APK-file-hash routine, remote-config "use_lf_aphash2"). Determine: does ACE read the cert from the APK FILE (openat/mmap of base.apk), from PMS, or is it fed by the game and validated SERVER-SIDE? Trace the result into a report field. This is the #1 ban cause for our re-signed build.` },
  { id: 'a2', lib: 'libanogs', surface: 'Report construction + kill switch',
    task: `Confirm the report pipeline and every kill switch. Decompile sub_3653D4 (report packer) — confirm the byte_3DB1EC gate at 0x3DB1EC and byte_3DB1ED at 0x3DB1ED. Trace COREREPORT/tdm_report/senddatatosvr (grep decoded_strings.txt + strings.json) to the submit function sub_365540. Verify: if byte_3DB1EC=0, is the PUSH path (senddatatosvr JNI, tss_sdk_send_data_to_svr callback) ALSO dead, or does it bypass the packer? Find the init self-kill kill(getpid(),9) site near sub_DBC9C.` },
  { id: 'a3', lib: 'libanogs', surface: 'maps / loaded-.so scanner',
    task: `Find who reads /proc/self/maps or enumerates loaded libraries, and the lib-name blocklist. grep decoded_strings.txt for "maps", "/proc", ".so", "dlopen", library names. search callers on any function referencing those strings. KEY QUESTION: is there a WHITELIST (only-these-libs-allowed) or a BLOCKLIST (these-cheat-libs-banned)? Our libmedia_codec.so is an unknown name — a whitelist bans us, a blocklist may not. Decompile the scanner and show its match logic.` },
  { id: 'a4', lib: 'libanogs', surface: '.text integrity / inline-hook detection',
    task: `Find the code-integrity scanner. Decompile sub_378E6C ("bin_patch_cnt" / "!skip:0x%08x, bin_patch_cnt:%d") and sub_24BC4C (ms_set_inlie_hook / inline_hook_opcode_dismatch / %s;crc:%s). Determine what memory it checksums: its OWN .text? libc .text? the game's? This decides whether our Dobby hooks on libanogs exports + libc getaddrinfo are detected. Show the compare logic and what triggers on mismatch.` },
  { id: 'a5', lib: 'libanogs', surface: 'Emulator / environment / debug detection that could hit BlueStacks',
    task: `Inventory environment checks that might fire on BlueStacks specifically (user tests there). grep decoded_strings.txt for emulator names (NOX/BlueStacks/vbox/genymotion/houdini/libnb), ptrace/TracerPid, /proc/cpuinfo, ro.product props. For each, cite the string + the function (search callers). Flag which are PROVEN to build a report vs just local. Note: FF server ALLOWS BlueStacks for legit guests, so separate "emulator flagged" from "emulator+tamper = ban".` },
  { id: 'a6', lib: 'libanort', surface: 'SVC syscall kill chain',
    task: `Map the raw-syscall kill chain. Run: search RAW/svc.json svc  → every SVC site with its R7 syscall number. Identify exit_group(0x-… R7=248), kill(R7=37), tgkill(R7=268), ptrace(R7=26). For the exit/kill ones, search callers backwards to what triggers them (a failed integrity check?). These raw SVCs bypass any libc hook — they are how ACE kills us uncatchably. Cite each SVC offset + R7 + the trigger function.` },
  { id: 'a7', lib: 'libanort', surface: 'libanort independent scanners (maps/file-integrity/RWX)',
    task: `libanort is a SECOND detection engine we have never hooked. Orient from exports.json (JNI_OnLoad 0xD988, tp_syscall_imp 0x108AF0, g_acf_array 0x15DB0C, g_aco_array 0x15F15C). Find its scanners: grep functions.json for high-xref functions; search str for "maps"/".so"/"mprotect"/RWX-related; decompile the top candidates. Does libanort independently scan maps, hash files on disk, or detect RWX/mprotect pages (which Dobby creates)? Does it have its OWN report/kill path separate from libanogs?` },
  { id: 'a8', lib: 'libanort', surface: 'String decryption (build the decoder)',
    task: `libanort strings are NOT decoded. Find the decoder family (grep functions.json for high xrefs_to functions taking one int arg returning char*; decompile 3-5 candidates to recover the XOR/rolling-key algo — compare to libanogs's decode_strings.py which uses key layout [key0][len^key0][cipher][chk], rolling k_{j+1}=((k_j+j)^XC)+AC, checksum (chk^XOR(out)^key0)&0xFF==0xFF). Port it to a Python script analysis/libanort/RAW/decode_strings.py, run it, and report how many strings decoded + the 20 most detection-relevant (cert/maps/hook/kill/report/emulator). This UNLOCKS the other libanort agents' string leads.` },
  { id: 'a9', lib: 'libanogs', surface: 'Network push path (the REAL report endpoint)',
    task: `Find where reports actually go on the wire. grep decoded_strings.txt + strings.json for host/endpoint strings: "listdl", "anticheatexpert", "garenanow", "freefiremobile", ":10012", http/https URLs, IP literals. For each, search callers to see who connects. Decompile the sender. KEY: we blackholed getaddrinfo(anticheatexpert) but the real channel may be glcs.listdl.com:10012 or the game-relayed senddatatosvr. Identify the ACTUAL production report endpoint(s) and the send syscall/function so a blackhole can target the right thing (or confirm byte_3DB1EC=0 makes all of them moot).` },
  { id: 'a10', lib: 'libanogs', surface: 'What MUST run for FF to boot (safety rail)',
    task: `Map the boot-critical ACE path so we never re-break boot (the AnoSDKInit NOP froze FF). Decompile AnoSDKInit (0xE6E04) → sub_DD960 → sub_DBC9C → sub_37C15C (the tss_sdk_send_data_to_svr handshake FF blocks on). Identify precisely which calls FF's resource download waits on. Deliverable: the list of functions/flags that are MUST-STAY-ALIVE vs SAFE-TO-NEUTER, so our .so touches only safe ones. Confirm byte_3DB1EC (report flag) is NOT on the boot-critical path.` },
]

phase('Sweep')
log(`Launching ${MISSIONS.length} sweep agents — each with its own IDA snapshot, decompiling OUR v7a bytes.`)

// Pipeline: each mission goes sweep → verify independently (no barrier).
const results = await pipeline(
  MISSIONS,
  // Stage 1: SWEEP
  (m) => agent(
    `${RULES}\n\nYOUR SNAPID: ${m.id}\nYOUR LIB: ${m.lib}\nYOUR SURFACE: ${m.surface}\n\nMISSION:\n${m.task}\n\n` +
    `Work the ida_snap.cmd tool hard — decompile the real functions, read the outputs, follow call graphs with 'search callers'. ` +
    `Return every detection you can PROVE in the bytes, each with its offset and the exact proof command.`,
    { label: `sweep:${m.id}:${m.surface.slice(0, 28)}`, phase: 'Sweep', schema: FINDING_SCHEMA, effort: 'high' }
  ),
  // Stage 2: VERIFY (adversarial — re-run the proof commands, kill hallucinated offsets)
  (swept, m) => {
    if (!swept || !swept.findings || !swept.findings.length) return swept
    const provenList = swept.findings
      .filter(f => f.confidence === 'PROVEN')
      .map((f, i) => `${i + 1}. [${f.offset} ${f.isa}] ${f.claim}\n   proof_cmd: ${f.proof_cmd}`)
      .join('\n')
    if (!provenList) return { ...swept, verified: [], verify_note: 'no PROVEN findings to verify' }
    return agent(
      `${RULES}\n\nYOUR SNAPID: ${m.id}v\nYOUR LIB: ${m.lib}\n\n` +
      `ADVERSARIAL VERIFICATION. Another agent claimed these PROVEN findings about how ACE detects us. ` +
      `Your job: RE-RUN each proof_cmd yourself (use your own snapid ${m.id}v), read the output, and decide if the claim ` +
      `actually holds in the bytes. Default to REJECTED if the offset is wrong, the function does something different, ` +
      `or the command doesn't prove the claim. Be skeptical — wrong offsets cause SIGILL when we patch.\n\n` +
      `CLAIMS TO VERIFY:\n${provenList}\n\n` +
      `Return the SAME schema, but in findings[] include ONLY the claims that SURVIVED your re-check, each with confidence=PROVEN ` +
      `and evidence = what your re-run actually showed. Put rejected ones in the summary with why.`,
      { label: `verify:${m.id}:${m.surface.slice(0, 24)}`, phase: 'Verify', schema: FINDING_SCHEMA, effort: 'high' }
    )
  }
)

// ── Phase 3: synthesize ──────────────────────────────────────────────────────
phase('Synthesize')
const verified = results.filter(Boolean)
const corpus = verified.map(r =>
  `### ${r.lib} — ${r.surface}\nSUMMARY: ${r.summary}\n` +
  (r.findings || []).map(f =>
    `- [${f.affects_us ? 'AFFECTS-US' : 'n/a'}] ${f.claim}\n  offset=${f.offset} isa=${f.isa} conf=${f.confidence}\n  proof=${f.proof_cmd}\n  avoid=${f.avoid || '(none given)'}`
  ).join('\n')
).join('\n\n')

log(`Sweep+verify done: ${verified.length}/${MISSIONS.length} surfaces returned. Synthesizing avoid-spec.`)

const SYNTH_SCHEMA = {
  type: 'object',
  required: ['ban_root_causes', 'build_spec', 'must_stay_alive', 'open_questions'],
  properties: {
    ban_root_causes: { type: 'array', items: { type: 'string' }, description: 'ranked, each with the proving offset — the actual reasons our build bans' },
    build_spec: { type: 'array', items: { type: 'string' }, description: 'concrete DO / DO-NOT rules for our libmedia_codec.so + smali build, each traceable to a finding' },
    must_stay_alive: { type: 'array', items: { type: 'string' }, description: 'ACE functions/flags we must NOT touch or boot breaks' },
    catalog_md: { type: 'string', description: 'full replacement text for analysis/DETECTION_CATALOG.md sections 1-4, in NOTE_STYLE with offsets' },
    open_questions: { type: 'array', items: { type: 'string' }, description: 'what is still unproven + the exact next ida_snap command to resolve it' },
  },
}

const synth = await agent(
  `${RULES}\n\nYou are the SYNTHESIS agent. Below are the VERIFIED findings from 10 sweep+verify agents, ` +
  `all proven in OUR v7a bytes. Merge them into a single coherent answer to the one question: ` +
  `"exactly how does ACE detect our smali-inject build, and what must our .so do / not do to survive?"\n\n` +
  `Rank the ban root-causes by how strongly the evidence supports them. Every rule in build_spec must trace to a finding's offset. ` +
  `Be honest about what is still GUESS vs PROVEN.\n\nVERIFIED FINDINGS:\n${corpus}`,
  { label: 'synthesize:avoid-spec', phase: 'Synthesize', schema: SYNTH_SCHEMA, effort: 'high' }
)

return { surfaces_covered: verified.length, missions: MISSIONS.length, synthesis: synth, raw: verified }
