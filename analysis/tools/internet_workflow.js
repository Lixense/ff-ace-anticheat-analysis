export const meta = {
  name: 'ace-internet-hunt',
  description: 'Multi-language internet research (parallel MCP) on how FF mods really beat ACE, source-validated and cross-checked against our proven detection facts',
  phases: [
    { title: 'Recon', detail: 'per-language + per-angle search, >=15 parallel-MCP calls each, log every source' },
    { title: 'Validate', detail: 'grade each source real-technique vs scam-download-farm; keep only real' },
    { title: 'CrossCheck', detail: 'score each surviving method against our byte-proven ban causes' },
    { title: 'Synthesize', detail: 'rank viable methods, write analysis/internet/METHODS.md' },
  ],
}

// Byte-proven ban facts every agent must score methods against (from PROVEN_DETECTION.md).
const PROVEN = `
OUR BYTE-PROVEN BAN CAUSES (from decompiling our own v7a libanogs/libanort — these are FACTS, not theory):
 #1 base.apk FILE HASH: libanogs sub_231B44 + libanort sub_5B87C hash the ON-DISK FILE fresh
    (sub_35CF60 re-reads disk, not memory). Our modified/re-signed apk hash != Garena's known hash. Server bans.
 #2 CERT: libanort sub_851D8 parses the v2 "APK Sig Block 42" NATIVELY from the on-disk apk — BELOW the
    Java PackageManager layer, so LSPatch/NPatch --sigbypass (Java-only) does NOT cover it. Our CN=Debug != Garena.
 #3 .text INTEGRITY: libanogs sub_17A590 memcmp live pages vs on-disk file (zero tolerance) + sub_2E7DF0 CRCs
    r-xp/RWX pages; libanort sub_F368E md5+crc32 of .text. => ANY inline/.text hook (Dobby) is caught. GOT/PLT or
    a trampoline in a fresh anon page outside r-xp is the only safe hook shape.
 #4 libanort SELF-PROTECTS its own .text (checksum VM sub_E24BC, 561 sites; self-kill sub_ED584 kill(getpid(),9)).
    You CANNOT byte-patch libanort. Verdicts leave via the GAME callback (tss_sdk_send_data_to_svr) AND libanort's
    own uploader sub_B6CDC — blackholing ACE CDNs is useless; only staying UNDETECTED works.
 Boot rail: AnoSDKInit(0xE6E04)->sub_DBC9C validates init_info(size==12) or SIGKILLs at 0xDC146. Full NOP froze boot.
A method from the internet is only "viable for us" if it survives ALL FOUR above. Score every method against them.
`

const SESSION = 'dripclienthgproxyhunt2026v3'  // fresh session — hunt Proxy architecture in English only

const RECON_RULES = `
You research how Free Fire / Tencent-ACE mobile game mods ACTUALLY bypass the anti-cheat. You are one of many
agents, each owning a LANGUAGE + ANGLE. Use the Parallel Search MCP HEAVILY.

HARD REQUIREMENTS:
1. Call mcp__parallel-search__web_search AT LEAST 15 TIMES (more is better). Vary queries each call. Use
   mcp__parallel-search__web_fetch on the 5-10 most promising REAL pages to read full technique detail.
2. SEARCH IN YOUR ASSIGNED LANGUAGE (write queries in that language's script), then translate findings to English
   in your output. Native-language modding scenes know things the English SEO farms never publish.
   For every web_search call pass: model_name:"claude-opus-4-8", session_id:"${SESSION}".
3. LOG EVERY SOURCE you touch to a JSON list: url, language, one-line what-it-claims, and your first-pass
   real-vs-farm guess. The next phase validates these — your job is BREADTH + capturing the mechanism.
4. HUNT FOR MECHANISM, NOT DOWNLOADS. We do NOT want "download this mod apk" pages. We want HOW: the technique,
   the tool, the hook point, the smali/native trick, the signature/integrity defeat, the injection method.
   Ignore diamonds/aimbot marketing; chase the anti-ban/anti-detection engineering.
5. Sites to prioritize: guidedhacking, unknowncheats, MPGH, XDA-developers, github (source repos + issues),
   YouTube (fetch tutorial URLs — read the description + captions if you can), Telegram channel indexes
   (tgstat.com / t.me/s/<channel>), Reddit r/FreeFireHacks r/androidHackerz, vendor sites (cheto.shop,
   hgcheats.com, and any panel-vendor page), VirusTotal (any DripClient/HG-Cheats APK submissions).
   Distrust and DOWN-WEIGHT getmodsapk/9mod/apkabc/*apk-download*.io farms — capture their URLs as
   "farm" evidence of a tool existing, but never treat their descriptions as mechanism.

6. THE CENTRAL MYSTERY YOU ARE HUNTING: DripClient Proxy, HG Cheats Proxy, and the "Proxy" panel family
   ship WORKING full-featured aimbot + ESP for Free Fire on NON-ROOT devices, updated for years. Our
   own byte-level analysis says this SHOULD be impossible (#1 file hash + #2 native cert both catch a
   modified apk). Something in the "Proxy" architecture beats this. Possibilities to actively test:
     (a) Proxy is a VpnService that intercepts+rewrites the game's TLS traffic (server-side manipulation,
         not process injection). If true → no cert/hash issue at all, they never touch the apk.
     (b) Proxy is an AccessibilityService that reads screen state + issues synthetic touches for
         aimbot/macros. No injection → nothing to detect client-side.
     (c) Proxy is a SYSTEM_ALERT_WINDOW overlay app that draws ESP on top of FF using accessibility
         info + touch-injection for aim assist. Same clean shape.
     (d) Proxy is a companion signed APK that shares userId (android:sharedUserId) with FF via a mod
         framework hook — needs same signature to work, so this would fail on non-root, but WORTH
         verifying that possibility is ruled out.
     (e) Proxy patches the game via KernelSU/Magisk stub bundled invisibly — verify user reports of
         "non-root" actually mean non-root vs bundled-root.
     (f) Something we haven't imagined. The point of the search is to FIND OUT WHICH.
   For every method you propose, EXPLICITLY answer: which of (a)-(f) is it, based on the sources you found?

7. NOTE — dead ends from prior research (do not re-propose):
   - NPatch (seccomp): the user already tested it via LSPatch and it was banned. Also v7a not shipped.
   - LSPatch --sigbypass alone: banned; #2 native cert parse beats Java-only sigbypass.
   - Static-NOP AnoSDKInit: froze boot (STATUS.md).
   - Dobby inline .text hooks on scanned libs: caught by #3.
   Focus on the Proxy architecture and any similarly-shaped non-injection mechanism.

OUTPUT the schema: a methods[] list (each = a distinct technical approach you found, with how-it-works +
source urls) and a sources[] log (every url with your farm/real guess).
${PROVEN}
`

const RECON_SCHEMA = {
  type: 'object',
  required: ['language', 'angle', 'methods', 'sources', 'search_count'],
  properties: {
    language: { type: 'string' },
    angle: { type: 'string' },
    search_count: { type: 'integer', description: 'how many web_search calls you actually made (must be >=15)' },
    methods: {
      type: 'array',
      items: {
        type: 'object',
        required: ['name', 'how_it_works', 'tools', 'source_urls', 'targets_which_ban_cause'],
        properties: {
          name: { type: 'string' },
          how_it_works: { type: 'string', description: 'the actual mechanism, concrete — hook point / tool / trick' },
          tools: { type: 'array', items: { type: 'string' } },
          source_urls: { type: 'array', items: { type: 'string' } },
          targets_which_ban_cause: { type: 'string', description: 'which of our #1-#4 proven ban causes this method would address' },
          language_found_in: { type: 'string' },
        },
      },
    },
    sources: {
      type: 'array',
      items: {
        type: 'object',
        required: ['url', 'claims', 'first_guess'],
        properties: {
          url: { type: 'string' },
          language: { type: 'string' },
          claims: { type: 'string' },
          first_guess: { type: 'string', enum: ['real-technique', 'download-farm', 'mixed', 'unknown'] },
        },
      },
    },
  },
}

// ── ENGLISH-ONLY DEEP RECON. Target: the actual "Proxy" architecture that DripClient / HG Cheats /
//    Cheto ship on non-root with FULL aimbot+ESP. "Proxy" = a companion app + game combo that WE do
//    not understand yet. Every agent chases the mechanism through vendor pages, telegram, youtube
//    transcripts, github, forums — and captures HOW the proxy actually talks to the game process.
//    12 English agents, each >=15 parallel-MCP searches, deep on named tools.
const RECON = [
  { lang: 'English', angle: 'DripClient Proxy — architecture, install steps, what the "proxy app" actually does',
    hint: 'DripClient proxy Free Fire how it works, drip client proxy setup tutorial step by step, drip client apk what is the proxy for, drip client v21 v22 setup, drip client architecture non root, dripclient proxy accessibility service, cheto shop drip client proxy — HUNT: is the proxy a VPN? an accessibility service? a companion signed app? a plugin? read every install tutorial you can find and reverse the mechanism.' },
  { lang: 'English', angle: 'HG Cheats Proxy — architecture, mechanism, decompile the installer if you can find it',
    hint: 'HG Cheats proxy Free Fire architecture, hg cheats injector how it works non root, hg cheats setup video crack, hg cheats telegram apk analysis, "proxy hg cheats" mechanism, hgcheats.com how it works, hgcheats aimbot esp mechanism — find github mirrors / vt uploads / any decompile / any teardown / any leak of the installer or panel.' },
  { lang: 'English', angle: 'Cheto Shop + FS Panel + Cuban Mods + Fs Panel — vendor panel architecture',
    hint: 'cheto.shop Free Fire panel architecture, FS panel Free Fire mechanism, Cuban Mods Free Fire panel non root, cheat vendor Free Fire panel v9 v10 how it works, Free Fire panel activation key architecture, Free Fire panel proxy vs injector difference, Free Fire panel accessibility service how it works — capture what technology each named panel actually uses.' },
  { lang: 'English', angle: 'The "Proxy app" pattern — is it VPN-based, Accessibility, Overlay, or a shim APK?',
    hint: 'Android game hack proxy app VPN local, Android accessibility service game aimbot hack, Android overlay app aimbot how it works, Free Fire proxy VPN loopback intercept traffic, Android VpnService intercept game packets aimbot, Android accessibility touch injection aimbot, Android system alert window aimbot esp, proxy app FF injection method architecture — chase EVERY meaning of "proxy" the FF scene uses.' },
  { lang: 'English', angle: 'YouTube tutorial transcripts + install videos — pull the real setup steps',
    hint: 'drip client proxy install tutorial youtube 2025 2026, hg cheats proxy setup tutorial youtube non root, free fire mod menu proxy install steps youtube, free fire panel activation tutorial youtube, freefire hack non root setup steps 2025 — fetch each youtube URL and read the description + captions. The tutorials LEAK the mechanism (accessibility toggles, VPN permission, overlay permission).' },
  { lang: 'English', angle: 'Telegram channel indexes — named tools and their leaked builds',
    hint: 'drip client telegram channel free fire, hg cheats telegram channel free fire, ff panel telegram channel apk, free fire mod menu telegram channel tool 2025 2026, telegram t.me free fire proxy panel, tgstat free fire hack channel, "telegram apk" free fire proxy tool download link — capture channel URLs + tool names + any leaked APK filenames the recon can then chase.' },
  { lang: 'English', angle: 'UnknownCheats / GuidedHacking / MPGH — Android FF+ACE technical threads',
    hint: 'unknowncheats free fire non root hack thread, guidedhacking free fire ACE bypass thread, guidedhacking dripclient hg cheats analysis, MPGH free fire hack thread, unknowncheats libanogs libanort thread, unknowncheats "APK signing block" native parser bypass, guidedhacking Zygisk PUBG Mobile FF Free Fire ACE — read the deep threads.' },
  { lang: 'English', angle: 'VirusTotal / APK analysis reports of DripClient / HG Cheats binaries',
    hint: 'DripClient apk virustotal, HG Cheats injector apk analysis, drip client apk permissions manifest analysis, hg cheats apk permission decompile, DripClient apk manifest system_alert_window bind_accessibility_service vpn_service, free fire proxy app permissions declared, apk permission list drip client hg cheats — find any teardown reports that leak the manifest permissions (that alone reveals overlay/accessibility/VPN mechanism).' },
  { lang: 'English', angle: 'GitHub — LGL Mod Menu family + il2cpp injectors used by these panels',
    hint: 'LGL mod menu github android, LGLTeam Android-Mod-Menu, ImGui il2cpp android mod menu github, free fire mod menu github source, octowolves hooking template mod menu, github "Free Fire" mod menu source, github il2cpp injector no root, code-developers freefire-esp-aimbot — find the actual source templates every vendor panel is built on top of.' },
  { lang: 'English', angle: 'Splitedresconfs + game config injection + external file drops',
    hint: 'free fire splitedresconfs config injection, free fire /Android/data com.dts.freefireth files contentcache config, free fire external json config sensitivity aim assist, free fire config files no injection, free fire panel writes config file /sdcard, free fire game asset bundles config splitedresconfs — is this how the "panels" work? drop JSON into game data dir with elevated sensitivity/aim-assist?' },
  { lang: 'English', angle: 'Zygisk / KernelSU / Magisk modules that ship WORKING FF hacks',
    hint: 'zygisk module free fire mod menu github, kernelsu module free fire hack, magisk module free fire aimbot esp, zygisk ff bypass ACE working, ZygiskFrida free fire, LSPosed module free fire mod menu, riru module free fire — HUNT the actually-shipping root-based mods to understand what needs a Zygisk shape and what does not.' },
  { lang: 'English', angle: 'Deep RE writeups: how ACE-based games are hacked in the wild (mechanism only)',
    hint: 'ACE anticheat Free Fire mechanism writeup 2024 2025, libanort libanogs bypass writeup github, "no root" full aimbot ESP Free Fire technical mechanism, external overlay full ESP aimbot possible how, Android game aim assist without process injection technical, blackhat defcon paper mobile game anticheat evasion — chase mechanism-only content, ignore download-farm noise.' },
]

phase('Recon')
log(`Launching ${RECON.length} recon agents across ${new Set(RECON.map(r=>r.lang)).size} languages — each makes >=15 parallel-MCP searches, logs every source.`)

const results = await pipeline(
  RECON,
  // STAGE 1: RECON (native language, >=15 searches)
  (r, _orig, i) => agent(
    `${RECON_RULES}\n\nYOUR LANGUAGE: ${r.lang}\nYOUR ANGLE: ${r.angle}\n\nSEARCH SEED (adapt + expand, do NOT stop at these — invent 15+ query variations):\n${r.hint}\n\n` +
    `Make AT LEAST 15 web_search calls in ${r.lang}. Then web_fetch the best real pages. Capture the MECHANISM of every anti-ban / anti-detection technique you find, with source urls. Log every url you touched.`,
    { label: `recon:${r.lang.slice(0,12)}:${r.angle.slice(0,22)}`, phase: 'Recon', schema: RECON_SCHEMA, effort: 'high' }
  ),
  // STAGE 2: VALIDATE sources (grade real-technique vs scam farm; verify claims by fetching)
  (recon, r, i) => {
    if (!recon || !recon.sources || !recon.sources.length) return recon
    const srcList = recon.sources.map((s,j)=>`${j+1}. [${s.first_guess}] ${s.url} — ${s.claims}`).join('\n')
    const methodList = (recon.methods||[]).map((m,j)=>`M${j+1}. ${m.name}: ${m.how_it_works} (src: ${(m.source_urls||[]).join(', ')})`).join('\n')
    return agent(
      `You VALIDATE research sources for a Free Fire/ACE bypass investigation. Another agent (${r.lang}, ${r.angle}) ` +
      `collected these sources + methods. Your job: separate REAL technical knowledge from SCAM DOWNLOAD FARMS and fake/AI-spam.\n\n` +
      `Use mcp__parallel-search__web_fetch (model_name:"claude-opus-4-8", session_id:"${SESSION}") to actually OPEN the ` +
      `questionable urls and judge. A source is a DOWNLOAD-FARM/FAKE if: it just sells an apk, says "100% safe/unlimited diamonds", ` +
      `has no technical mechanism, is SEO spam, or the "tutorial" is content-free. A source is REAL if it shows actual code, ` +
      `hook points, tool names, disassembly, smali, a github repo with commits, or a substantive forum thread by a known researcher.\n\n` +
      `SOURCES:\n${srcList}\n\nMETHODS CLAIMED:\n${methodList}\n\n` +
      `Return the SAME recon schema, but: in sources[] set first_guess to your VERIFIED verdict (real-technique/download-farm/mixed), ` +
      `and in methods[] KEEP ONLY methods backed by at least one REAL source (drop farm-only methods). Note dropped ones in the angle field.`,
      { label: `validate:${r.lang.slice(0,10)}`, phase: 'Validate', schema: RECON_SCHEMA, effort: 'high' }
    )
  }
)

// ── Phase 3: CROSS-CHECK each validated method against our byte-proven ban causes ──
phase('CrossCheck')
const validated = results.filter(Boolean)
// Flatten all real methods, dedup by name.
const seen = new Set()
const allMethods = []
for (const v of validated) {
  for (const m of (v.methods || [])) {
    const k = (m.name || '').toLowerCase().trim()
    if (k && !seen.has(k)) { seen.add(k); allMethods.push(m) }
  }
}
log(`Validate done: ${validated.length}/${RECON.length} angles returned. ${allMethods.length} distinct real methods to cross-check against proven detection.`)

const SCORE_SCHEMA = {
  type: 'object',
  required: ['method', 'verdict', 'beats', 'defeated_by', 'reasoning'],
  properties: {
    method: { type: 'string' },
    verdict: { type: 'string', enum: ['VIABLE', 'PARTIAL', 'DEAD', 'UNKNOWN'] },
    beats: { type: 'array', items: { type: 'string' }, description: 'which of our #1-#4 proven ban causes this method actually defeats' },
    defeated_by: { type: 'array', items: { type: 'string' }, description: 'which of #1-#4 still catch it' },
    reasoning: { type: 'string', description: 'concrete, tied to the byte-proven facts' },
    what_wed_need: { type: 'string', description: 'what we would have to build/verify to use it' },
  },
}

const scored = await parallel(allMethods.map((m) => () => agent(
  `You are a skeptical anti-cheat engineer. Score ONE internet-sourced FF-mod method against our BYTE-PROVEN ban causes. ` +
  `Do not trust the method's own marketing — reason from the proven facts. Default to DEAD/PARTIAL unless it genuinely clears ALL FOUR.\n\n` +
  `${PROVEN}\n\nMETHOD TO SCORE:\nName: ${m.name}\nHow it works: ${m.how_it_works}\nTools: ${(m.tools||[]).join(', ')}\n` +
  `Claims to target: ${m.targets_which_ban_cause}\nSources: ${(m.source_urls||[]).join(', ')}\n\n` +
  `You MAY use mcp__parallel-search__web_fetch (model_name:"claude-opus-4-8", session_id:"${SESSION}") to open a source and confirm the mechanism before scoring. ` +
  `Decide: does it beat #1 file-hash, #2 native cert parse, #3 .text-integrity, #4 libanort-selfprotect+report? Be honest.`,
  { label: `score:${(m.name||'?').slice(0,30)}`, phase: 'CrossCheck', schema: SCORE_SCHEMA, effort: 'high' }
)))

// ── Phase 4: synthesize ──
phase('Synthesize')
const viable = scored.filter(Boolean)
const ranked = viable.filter(s => s.verdict === 'VIABLE' || s.verdict === 'PARTIAL')
const corpus = viable.map(s =>
  `### ${s.method} — ${s.verdict}\n beats: ${(s.beats||[]).join('; ')||'nothing'}\n defeated_by: ${(s.defeated_by||[]).join('; ')||'—'}\n why: ${s.reasoning}\n need: ${s.what_wed_need||''}`
).join('\n\n')

const SYNTH_SCHEMA = {
  type: 'object',
  required: ['viable_methods', 'combined_strategy', 'hidden_tricks', 'dead_ends', 'next_actions'],
  properties: {
    viable_methods: { type: 'array', items: { type: 'string' }, description: 'methods that beat or partially beat our proven ban causes, ranked best-first, each with which causes it clears' },
    combined_strategy: { type: 'string', description: 'the best COMBINATION of methods that could clear ALL of #1-#4, concretely' },
    hidden_tricks: { type: 'array', items: { type: 'string' }, description: 'the non-obvious / hard / rarely-documented techniques found (esp. from non-English scenes) that we did not already know' },
    dead_ends: { type: 'array', items: { type: 'string' }, description: 'popular methods proven DEAD against our detection, so we never retry them' },
    next_actions: { type: 'array', items: { type: 'string' }, description: 'concrete next steps to implement/verify the top strategy' },
    methods_md: { type: 'string', description: 'full text for analysis/internet/METHODS.md — every viable method, its mechanism, sources, and score vs #1-#4' },
  },
}

const synth = await agent(
  `You are the synthesis lead. ${validated.length} multi-language research angles found real FF/ACE bypass methods; ` +
  `each was scored against our four byte-proven ban causes. Produce the actionable answer to: ` +
  `"HOW do mods ship working FF hacks for years — what method (or combination) actually beats #1 file-hash, #2 native cert, ` +
  `#3 .text integrity, #4 libanort self-protect+report — and what do WE do next?"\n\n${PROVEN}\n\n` +
  `Especially surface HIDDEN/HARD tricks from the Chinese/Russian/Vietnamese scenes that we would not find in English. ` +
  `Be concrete and honest: if the only real answer is "burner accounts + accept bans", say so. If there is a genuine engineering ` +
  `path, spell out the combination.\n\nSCORED METHODS:\n${corpus}`,
  { label: 'synthesize:internet-methods', phase: 'Synthesize', schema: SYNTH_SCHEMA, effort: 'high' }
)

return { angles: validated.length, methods_found: allMethods.length, viable: ranked.length, synthesis: synth, scored: viable }
