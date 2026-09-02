# ff-ace-anticheat-analysis

> Reverse engineering notes on Tencent ACE (Anti-Cheat Expert) as it ships inside Free Fire
> (armeabi-v7a, OB54). Everything in here comes from decompiling the two ACE libraries
> ourselves and running the game against real builds. This repo is a POST-MORTEM. It
> exists so the next person doesn't waste months of their life on the same wall we did.

Author: Lixense (haithem08)  
What this is: research writeup + tooling. No cheat code, no working bypass, no APKs, no ACE binaries.

## Why this repo exists

I spent months trying to build a non-root panel for Free Fire on Android. Every approach
worked on paper and then died on the device. Somewhere along the way I got tired of the
same forums repeating the same wrong answers, so I sat down with IDA and my own tools and
went to prove what actually happens. This is what I found. If you are here because you are
about to start the same project, please read the whole thing first.

Short version: ACE is not just an SDK you can outsmart with a clever hook. It is a
kernel-adjacent (via raw SVC syscalls that skip libc), two-library, self-guarding,
server-validated stack. Every "solution" the modding scene sells for it is either a
different architecture than the one you are picturing, or it is a burner-account operation
that eats bans as cost of business. You cannot beat this from inside the game process on
a non-root device. This repo shows why, at the byte level.

## What Tencent ACE actually is

Everyone calls it "the anti-cheat" like it is one thing. It is not. It is two shared
libraries that guard each other, plus a server component you never see. The client side
lives in two `.so` files inside the game APK:

* `libanogs.so` (about 4 MB on our v7a build): the outward-facing engine. Exports the
  `AnoSDK*` API the game calls into, holds the string table, builds the detection reports.
* `libanort.so` (about 1.4 MB): the guard. Runs 114 raw ARM SVC syscall sites, checksums
  its own `.text`, ships an independent scanner and uploader, self-kills on any tamper.

Verdicts do not fly out through some ACE-owned socket you can blackhole. They travel
through the game's own network callback (`tss_sdk_send_data_to_svr`). Tencent's server
correlates missing or malformed reports and bans the account, not the process. So the
"just block anticheatexpert.com" trick every tutorial suggests does nothing. The report
was going to Garena's game servers the whole time.

People say ACE is "kernel level" as shorthand for two things that are both true here.
First, its ARM-mode SVC bank sits below libc, so any PLT or inline hook you put on
`open` / `read` / `mmap` / `connect` is bypassed at will. Second, its self-integrity is
tight enough that a single byte change anywhere in `libanort.so` .text (checksum VM at
`sub_E24BC`, 561 call sites, self-kill at `sub_ED584` via `kill(getpid(), 9)`) is fatal
to the process. That is a userland detail, not a kernel one, but the practical effect is
the same. You cannot patch it. You cannot hook it invisibly. You cannot be inside its
process without leaving trace it will find.

## What this repo contains

```
analysis/
  README.md                          workspace intro
  PLAYBOOK.md                        how the analysis fleet ran, mission by mission
  ORCHESTRATION.md                   how the parallel IDA workflow was orchestrated
  NOTE_STYLE.md                      the format every findings note follows
  PROVEN_DETECTION.md                the master answer to "how does ACE catch us"
  DETECTION_CATALOG.md               early avoid-list, superseded by PROVEN_DETECTION
  libanogs/
    IDENTITY.txt                     md5 + size + FF version the .so was pulled from
    notes/01_exports.md              21 AnoSDK exports, the JNI bridge, entry points
    notes/02_init_flow.md            AnoSDKInit chain, boot dependencies, do-not-touch
    notes/03_string_decryption.md    the 92-variant XOR/rolling-key decoder + how to run it
    notes/04_detection_targets.md    what ACE actually looks for (cert, apk hash, root, etc.)
    notes/05_kill_chain.md           the report path, the self-kills, the SVC bank
  libanort/
    IDENTITY.txt                     md5 + size + FF version
    notes/                           empty. See "what is missing" below.
  internet/
    METHODS.md                       synthesis from ~90 agents researching real-world FF mods
  tools/
    ida.cmd / ida.sh                 one-liner wrapper around idat.exe for repeatable queries
    ida_snap.cmd                     snapshot-per-agent so N idat processes can query the same
                                     .i64 concurrently (IDA locks a .i64 to one opener)
    ida_inventory.py                 first-pass corpus builder (functions, strings, exports, ...)
    ida_bulk_decompile.py            optional whole-corpus decompile (slow)
    ida_detection_hunt.py            keyword-driven detection sweep (7s libanogs, 3s libanort)
    ida_decompile.py                 targeted Hex-Rays decompile of named functions
    ida_search.py                    SVC / imm / bytes / str / callers search modes
    ida_decoder_args.py              grabs decoder call-site args (string-id -> plaintext)
    detection_workflow.js            the 21-agent parallel IDA workflow that produced PROVEN_DETECTION
    internet_workflow.js             the ~90-agent parallel web workflow behind internet/METHODS.md
    hist.py                          sqlite index over detections/findings/runs (searchable)
```

The two `.so` binaries and their IDA databases are NOT shipped. Every note tells you the
exact offset and the exact `ida_snap.cmd` line that produced it, so anyone who wants to
reproduce a claim extracts the same version of Free Fire, points IDA at its own
`libanogs.so` / `libanort.so`, and reruns the command.

## The reproducer, if you want to check the numbers

You need Free Fire OB54 v1.126.1 armeabi-v7a. The exact bytes we analyzed:

```
libanogs.so   md5 2810a5336fe644240a8d23885c7c5de4   size 3973352
libanort.so   md5 45cdcf19a674fc7336bb5c560e13f11a   size 1406804
```

Pull the arm split from your own APK, put the two `.so` files under
`analysis/libanogs/` and `analysis/libanort/`, then:

```
analysis\tools\ida.cmd libanogs inventory      # first-pass build, ~2-3 min per lib
analysis\tools\ida.cmd libanort inventory
analysis\tools\ida.cmd libanogs hunt           # detection sweep, 7 sec
analysis\tools\ida.cmd libanogs decompile RAW\out.txt AnoSDKInit
```

Every finding in `analysis/libanogs/notes/*.md` cites the exact command. If a claim does
not match your bytes, tell me. Either Tencent changed something, or my note is wrong.
Either way it should be fixable in an evening.

## What we proved (byte-level, no theory)

Full detail in `analysis/PROVEN_DETECTION.md`. Ranked by strength of evidence:

1. Modified `base.apk` file hash is the primary ban cause. Two independent libraries hash
   the APK from disk (`libanogs sub_231B44` at `0x231B44`, reached from dispatcher
   `sub_23267C`; `libanort sub_5B87C` at `0x5B87C` via `fopen + fread + checksum`).
   Both re-open the file fresh through `sub_35CF60`. A runtime memory patch cannot
   forge this. The server compares the client reported hash against Garena known good.

2. Re-signed cert (`CN=Debug`, whatever you signed with, anything not Garena) is caught
   twice. `libanogs` computes a `cert_md5` from the same APK CRC path. `libanort sub_851D8`
   parses the v2 APK Signing Block ("APK Sig Block 42") natively from disk, BELOW the
   Java `PackageManager` layer that `LSPatch --sigbypass` covers. So sigbypass at
   level 2 is not enough. It does not touch the native parse.

3. Inline (`.text`) hooks on any scanned module are caught. `libanogs sub_17A590`
   memcmps live pages against the on-disk file (`sub_34EE46` is a byte-exact primitive,
   zero tolerance). `sub_2E7DF0` mprotects `r-xp` pages RWX and CRCs them. `libanort
   sub_F368E` walks ELF32 section headers and md5+crc32 of `.text`. Every Dobby-style
   inline hook you place on `libc`, `libil2cpp`, or ACE own libraries changes the
   first bytes of a target function. That is exactly what these scanners look for.

4. `libanort` self-protects. 561 call sites feed a checksum VM at `sub_E24BC` that
   self-kills at `sub_ED584` (`kill(getpid(), 9)`) if the constant does not match. You
   cannot patch `libanort` at rest to disable it. You cannot patch it at runtime either
   without immediately tripping the VM.

Plus a boot rail we discovered the hard way: `AnoSDKInit` at `0xE6E04` builds an
`init_info` struct that `sub_DBC9C` validates. Break the size or the game_id, and the
worker `SIGKILL`s at `0xDC146`. A full NOP of `AnoSDKInit` (a popular "just skip the
anti-cheat" idea) froze Free Fire boot because the game blocks on
`tss_sdk_send_data_to_svr` being wired up. So you can not just remove ACE either.

## What we tried and why every single one failed

This is the part I wish someone had written for me a year ago.

### LSPatch (Xposed-style injection) with signature bypass

Idea: patch the APK with LSPatch, use `--sigbypass 2` to spoof `PackageManager` so the
Java `signingInfo` looks like Garena, inject a companion module. Result: instant ban.
Reason: `libanort sub_851D8` reads the v2 signing block off the FILE, not via
`PackageManager`. Sigbypass level 2 spoofs the Java view only. The native parse still
sees your `CN=Debug`. Plus the LSPatch loader dex ships identifiable strings
(`de.robv.android.xposed.*`, `LSPAppComponentFactoryStub` in the manifest,
`assets/lspatch/*`) that a maps-scan or a class-search catches trivially.

### NPatch (Neo LSPatch) with sigbypass level 4 (seccomp)

Idea: NPatch adds an SVC-level file redirector using seccomp-BPF to catch even raw
syscalls that skip libc. Sounded promising because it maps to exactly how `libanort`
does file I/O. Result: instant ban. Reasons: NPatch own runtime footprint (loader
files, framework classes, injected process attributes) is detectable independent of
whether the seccomp redirect works. Also NPatch upstream does not ship an armeabi-v7a
build, only arm64 and x86_64, so we could not use it on the FF v7a target anyway.

### Static NOP of `AnoSDKInit` (skip the anti-cheat entirely)

Idea: replace `AnoSDKInit` with a stub that just returns success. If ACE never
initializes, no scans, no reports, no bans. Result: Free Fire froze at resource download.
Reason: the game boot chain calls `AnoSDKInit`, which wires the report callback the game
itself uses (`tss_sdk_send_data_to_svr`). No callback wired means the game blocks
forever waiting for the ACE handshake. You cannot skip ACE. The game needs it running.

### Dobby inline hooks on libanogs exports + libc

Idea: hook `AnoSDKGetReportData` / `AnoSDKGetReportData2/3/4` to return NULL (no report),
hook `AnoSDKOnRecvSignature` to feed Garena cert bytes, hook `getaddrinfo` to blackhole
the report host. All hooks installed successfully. Confirmed firing in logcat. Result:
instant ban. Reason: covered above under #3. `sub_17A590` and `sub_F368E` see the
modified first bytes of every hooked function and report it. And the ban travels through
the game callback anyway, so the DNS blackhole was meaningless.

### Runtime write to `byte_3DB1EC = 0` (ACE own kill switch)

Idea: `libanogs sub_3653D4` (the master report packer) checks `byte_3DB1EC` at the top
and returns NULL if zero. Write zero to that byte at load time and the entire
report pipeline dies. Result: still instant-banned. Reason: `libanort` has its own
independent report path (`sub_60D86` sink, `sub_B6CDC` uploader), completely separate
from `libanogs`. Flipping the libanogs flag silences ONE of TWO engines. `libanort`
kept talking.

### Smali inject `System.loadLibrary("media_codec")` into the game FFApplication

Idea: no framework at all. Just apktool-decompile the APK, drop our `.so` into
`lib/armeabi-v7a/`, add one line of smali to load it, re-sign with our own key. Zero
Xposed footprint. Result: instant ban. Reason: the re-sign changes the APK v2 signing
block, which changes `cert_md5` AND the APK file hash. Both are covered by ban cause #1
and #2 above.

## Why non-root Unity + ACE cannot be beaten from inside the game process

Read this carefully. This is the honest, byte-proven conclusion.

To get code running inside Free Fire process on a non-root device, you have to either
inject an Xposed-family framework (LSPatch, NPatch, Zygisk without root) or modify the
APK and re-sign it. Both paths leave one or more of:

* a modified `base.apk` (hash differs from Garena known good)
* a re-signed cert (differs from Garena real cert)
* a modified `.text` of some library (`.text` differs from the on-disk file)
* an extra `.so` in `/proc/self/maps` with recognisable framework strings
* a manifest change (`appComponentFactory`, custom classes)

ACE has a dedicated, byte-proven scanner for each one of those. The scanners run out of
`libanort` (which is byte-locked by its own checksum VM), so you cannot silence them
without patching a library you cannot patch. And the report they build travels out
through the game OWN network callback, so blackholing "the anti-cheat domain" is a
red herring. There is no domain of ACE own that matters.

There is exactly ONE non-injection architecture that survives all of the above on
non-root: run your cheat in a SEPARATE process, from a separate signed APK, and observe
Free Fire from outside. That is what tools like the "Proxy" family (DripClient, HG
Cheats, Cheto) actually do. They combine `MediaProjection` frame capture, an
`AccessibilityService`, and either Shizuku-elevated `uinput` or synthetic gestures.
Free Fire itself stays stock from Play Store. Nothing inside its process changes. That
is the only shape that clears all four proven ban causes at once. Full technical
breakdown in `analysis/internet/METHODS.md`.

The catch: that architecture trades true memory ESP and true memory aimbot for
pixel-vision plus gesture injection. That is a smaller product than most people
picture when they say "mod menu". If you want the real thing (read enemy positions and
write to the game own aim-assist pointer), you need one of:

* a rooted Android device, so you can run outside FF UID and still read its memory
* a Windows PC + emulator that exposes guest memory (BlueStacks + VMM works today)
* your own kernel driver on Android, which is the actual anti-cheat arms race

Anything advertised as "non-root full aimbot in a mod menu inside Free Fire" is either
lying about non-root, lying about aimbot, or ban-cycling weekly and pricing that into
the subscription. There is no fourth option and no clever hook that changes this.

## What is missing, and what would be worth adding

I did not finish everything. If you want to contribute or fork, these are the highest
value gaps:

* `analysis/libanort/notes/`: empty. libanort was reversed enough to prove the four ban
  causes above, but a full notes set (exports, init, string decoder, scanner inventory,
  SVC map) does not exist yet. The tools are all here; a good IDA session is a weekend.
* Bundle-level integrity check: FF ships hash-addressed AssetBundles in
  `/Android/data/com.dts.freefireth/files/contentcache/...`. Nothing in libanogs or
  libanort I decompiled walks that tree, which SUGGESTS but does not PROVE that dropping
  a modified bundle is undetected. Someone should confirm the hash-name lookup is the
  only integrity gate on those files.
* The exact server correlation window is a black box to me. I know a modified apk hash
  in the report causes a ban within ~10 seconds of first successful login. I do not
  know if hash-of-nothing (report suppressed) is also a ban within some window, or if
  the server truly is fail-open on absent reports.

## Ethics and framing

I did this work to understand, not to sell. This repo does not ship a working cheat, a
signed APK, a keystore, a working `libmedia_codec.so`, or any redistributable
Tencent/Garena binary. The takeaway is deliberately "here is why the popular non-root
approaches do not work", not "here is a bypass".

If you are a security researcher: welcome, PRs welcome, especially on the libanort side.  
If you are an anti-cheat engineer: yes, hi, your product is impressive from the inside.  
If you are here to ship a cheat: read the section above titled "Why non-root Unity + ACE
cannot be beaten from inside the game process", then decide if it is really the project
you want to spend the next six months on.

## Credits and prior art

* `msantiagodev/ACE-ANTICHEAT` on GitHub is the arm64 / UE4 reference notes. Great for
  understanding how ACE thinks in general. Every specific offset in there is arm64
  and does not map to our v7a bytes, which is exactly why this repo exists.
* Il2CppDumper by Perfare, without which none of the game side offsets would be knowable.
* IDA Pro Hex-Rays, still the state of the art for this kind of work.
* The parallel-search MCP and the workflow tool that let me run 90+ concurrent research
  agents to grind through the modding scene faster than a human could.

## Contact

Open an issue on this repo. Include the specific offset you are questioning and the
`ida_snap.cmd` line you ran. Do not ask me for a working cheat, do not ask for a signed
APK, do not ask how to unban an account. If you have a legitimate research question
about how a specific detector in libanogs or libanort actually works, I will help.
