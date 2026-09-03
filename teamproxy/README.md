# teamproxy / the proxy TEAM panel teardown

everything we pulled out of the "SX2 TEAM PROXY" free fire panel
(com.Sx2.Team.Ban). this is the raw evidence folder for the expose section in
`analysis/README.md`. nothing here is theory, everything came out of his apk, his
server responses, his runtime data or his native lib.

## the one line story

he sells a "panel" that is really just an esp file injector. it needs shizuku, it needs
your license key + your device id, it drops a hybridclr hotfix into the game data dir
and the hotfix draws walls. no aimbot exists anywhere in it. and the esp part is exactly
the kind of thing that gets accounts flagged.

## what is in here

- `README_FINDINGS.md` the full technical writeup, all layers, all keys, all commands
- `base.apk` his app, 41mb, gitignored but on disk (also in inner_apk_work/)
- `sx2_runtime_data.tgz` full /data/data pull after the app unpacked itself (root)
- `xor_key.txt` the 6978 char arabic diacritics static xor key that decrypts his strings
- `payload_modes/` the 4 "modes" extracted from assets/ALL01.zip, each with the
  localconfig.json + the Assembly-CSharp-patch.bytes hybridclr hotfix
- `payload_inner/` the decrypted inner vault (his original manifest, resources, media)
- `decompiled/` the apktool smali of all 6 dexes
- `ghidra_out/` the ghidra headless decompile of his native lib123.so (787 functions)
- `com.Sx2.Team.Ban/` the live runtime tree pulled off the emulator
- `libXZAXZAXZAXZA.so.enc` / `libZZZZZZZZZZZZ.so.enc` / `libQWERTYUIOPAS.so.enc`
  the 3 server side native libs, still encrypted (see below)
- `analysis_scripts/` every decrypt script used, including the frida attempts

## the protection stack he used

1. np.protect style shell, real assets encrypted inside a folder nested 1000 levels deep,
   only unpacked at runtime
2. every class and method renamed to chinese poetry fragments, the smali is a wall of
   将进酒 lines
3. every string is base64 of hex, then xor with the big arabic diacritics key
4. the app logic lives in native lib123.so (a dex2c style jni engine) and its rodata
   string table uses the same xor scheme

## how it was cracked

- the java string layer: recovered the xor key, wrote a decoder, dumped every string
- the native layer: ghidra headless on lib123.so, recovered the 164 key+cipher pairs in
  rodata, decoded them all with the same scheme
- the payloads: assets/ALL01.zip holds mode folders 1F/2F/3F/4F, extracted them
- the runtime: pulled the data dir after the app ran, got his Data.xml (your license key
  plus his api_key_free), device_prefs.xml (device id), the auxv anti debug file

## what is still locked

the 3 server .so files. his hotfix downloads them with AES/CTR and a key string that is
in the patch (f7a2c9d1e8b34560ac7ef1230d9b56e4) but the real key/iv is derived at runtime
in the hybridclr il, not the literal string. we tried every obvious key + iv combo in
python and inside his own app jvm via frida, none produces an elf. to finish it you need
to run the hotfix inside a real ff process and dump the lib from memory after load, or
disassemble the hybridclr method body. detail in README_FINDINGS section 10.

## why esp and never aimbot, and why even esp bans you

short version: writing camera angles inside the game process is the most detected thing
in anticheat and a file drop panel cannot do it. the hotfix dll can only add managed
ui logic, so walls are the ceiling. and the walls still leave localconfig.json
testCodePatch, a foreign .so loaded into the process, reporfnew.db and a shader cache
marker, plus he logs your device id on his server every time you open the panel.
full version in `analysis/README.md` under exposed panels.
