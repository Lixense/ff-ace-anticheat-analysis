# libanogs.so — Exported API & JNI Dispatch Surface (our v7a analysis)

> Source of truth: OUR analysis/libanogs/libanogs.so (md5 2810a533, from IDENTITY.txt).
> Cross-ref hint (verify, don't trust): INFO/ace_anticheat_notes/66_libanogs_jni_native_api.md and 32_jni_native_methods.md — arm64 build.

## Summary

`libanogs.so` exports 21 dynamic ELF symbols (`AnoSDK*` and `JNI_OnLoad`) and registers two distinct `JNINativeMethod` dispatch tables during `JNI_OnLoad`: a 3-method test table on `com/tss/gamedemo/Game` and an 11-method production table on `com/gamesafe/ano/AnoSdk`. These entry points form the complete boundary between the Free Fire client (both Unity/native and Android Java runtimes) and the ACE anti-cheat engine. Understanding this boundary is critical to ban evasion: statically neutering `AnoSDKInit` breaks the game's internal handshake and deadlocks resource downloading (PROVEN runtime freeze), while selectively intercepting the telemetry extraction APIs (`AnoSDKGetReportData`, `senddatatosvr`) exposes and isolates detection payloads.

## Evidence — ELF Dynamic Exports (21 symbols)

Extracted from `RAW/exports.json` and decompiled in `RAW/m1_*.c`, `RAW/m1_all_exports.c`, and `RAW/m2_decomp_batch1.txt`:

| Offset (RVA) | Symbol / our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0xE6E04 | `AnoSDKInit` | Thumb | Bootstraps anti-cheat core via `sub_DD960(game_id)` -> `sub_DBC9C`; registers monitor module 0 via `sub_36570C(a1 > -1, 0)`. | exports.json; RAW/m2_decomp_batch1.txt |
| 0xE70B8 | `AnoSDKInitEx` | Thumb | Extended SDK initialization taking a 64-bit config argument; flattened dispatcher tail-calls `sub_DDF34(a1, HIDWORD(a1))`. | exports.json; RAW/m1_AnoSDKInitEx.c |
| 0xE78AC | `AnoSDKSetUserInfo` | Thumb | Ingests account type `a1` and UID `a2`; calls `sub_DA860(a1, 0, a2, &byte_60B24)` and arms monitor module 1 via `sub_36570C(cond, 1u)`. | exports.json; RAW/m1_AnoSDKSetUserInfo.c |
| 0xE7BD8 | `AnoSDKSetUserInfoWithLicense` | Thumb | Extended user info with license key `a3`; calls `sub_DE8B4(a1, 0, a2, &byte_60B24, a3)` and arms monitor module 1 via `sub_36570C(cond, 1u)`. | exports.json; RAW/m1_AnoSDKSetUserInfoWithLicense.c |
| 0xE833C | `AnoSDKOnPause` | Thumb | Lifecycle pause handler; arms monitor module 2 via `sub_36570C(1, 2u)`, sets state via `sub_DEAFA(2)`, notifies `sub_36570C(92, 0x10u)`. | exports.json; RAW/m1_AnoSDKOnPause.c |
| 0xE85F4 | `AnoSDKOnResume` | Thumb | Lifecycle resume handler; sets active state via `sub_DEAFA(1)` and arms monitor module 3 via `sub_36570C(1, 3u)`. | exports.json; RAW/m1_exports_rem.c |
| 0xE8B4A | `AnoSDKGetReportData` | Thumb | Fetches queued detection report buffer; triggers monitor 4 via `sub_36570C(1, 4u)` and pulls payload via `sub_D6AC0()`. | exports.json; RAW/m1_AnoSDKGetReportData.c |
| 0xE9420 | `AnoSDKDelReportData` | Thumb | Acknowledges/frees report buffer at pointer `a1` via `loc_D63B4(a1)`; notifies monitor 5 via `sub_36570C(1, 5u)`. | exports.json; RAW/m1_AnoSDKDelReportData.c |
| 0xE9C42 | `AnoSDKOnRecvData` | Thumb | Ingests security command/ticket payload `a1` (length `a2`) from server; notifies monitor 6 via `sub_36570C(cond, 6u)` and routes to `sub_D72E0`. | exports.json; RAW/m1_AnoSDKOnRecvData.c |
| 0xE9F5E | `AnoSDKIoctlOld` | Thumb | Legacy 4-argument ioctl command interface; control-flow flattened jump to dispatcher `0xD99B0`. | exports.json; RAW/m1_AnoSDKIoctlOld.c |
| 0xEA944 | `AnoSDKIoctl` | Thumb | Modern ioctl entry point taking packed 64-bit argument struct `a1`; control-flow flattened call to `sub_DC804(a1)`. | exports.json; RAW/m1_AnoSDKIoctl.c |
| 0xEB11E | `AnoSDKFree` | Thumb | SDK shutdown and cleanup routine; calls `sub_DD41C(a1)`. | exports.json; RAW/m1_AnoSDKFree.c |
| 0xEB844 | `AnoSDKGetReportData2` | Thumb | Secondary detection report buffer retrieval; directly tail-calls `sub_DB3D0()`. | exports.json; RAW/m1_AnoSDKGetReportData2.c |
| 0xEB88A | `AnoSDKGetReportData3` | Thumb | Tertiary detection report buffer retrieval; directly tail-calls `sub_DFB2C()`. | exports.json; RAW/m1_all_exports.c |
| 0xEB8D0 | `AnoSDKDelReportData3` | Thumb | Category 3 report buffer free stub; returns constant `-715586084` (`0xD556B81C`). | exports.json; RAW/m1_all_exports.c |
| 0xEBFE4 | `AnoSDKGetReportData4` | Thumb | Quaternary detection report buffer retrieval; indirect call via `*((char*)&off_E0508 + 2)` (`0xE050A`). | exports.json; RAW/m1_all_exports.c |
| 0xEC282 | `AnoSDKDelReportData4` | Thumb | Category 4 report buffer free stub; returns constant `-715586084`. | exports.json; RAW/m1_all_exports.c |
| 0xEC996 | `AnoSDKOnRecvSignature` | Thumb | Server signature validation handler; calls `sub_E0D0C(a1, a2, a3, a4)` to verify package/cert digest. | exports.json; RAW/m1_all_exports.c |
| 0xECC40 | `AnoSDKRegistInfoListener` | Thumb | Registers security event callback `a1`; allocates 8-byte wrapper via `sub_394094(8)` and registers via `sub_DC604`. | exports.json; RAW/m1_all_exports.c |
| 0xECF4C | `AnoSDKForExport` | Thumb | Export integrity canary; directly tail-calls `sub_E6DC8()`. | exports.json; RAW/m1_all_exports.c |
| 0xEEE94 | `JNI_OnLoad` | Thumb | JVM initialization entry point; extracts `JNIEnv`, dynamically resolves and registers JNI methods on Class 1 and Class 2, returns `0x10004` (`JNI_VERSION_1_4`). | exports.json; RAW/m2_decomp_jnionload.txt; RAW/m1_asm_onload.txt |

## Evidence — JNI Registration & Native Dispatch Tables

### Class 1: `com/tss/gamedemo/Game` (3 methods, test/demo class)

Target class name decrypted from string ID 3164 (`sub_37FD58(3164) -> "com/tss/gamedemo/Game"`). Static registration table located at `off_3A7250` (36 bytes):

| Slot | Method Name | Java Signature | Native Handler RVA | ISA | What it does |
|---|---|---|---|---|---|
| 0 | `init` | `()I` | 0xED89E | Thumb | Invokes test initialization engine (`sub_DD960`). |
| 1 | `onPause` | `()I` | 0xEDB1C | Thumb | Test pause lifecycle hook (`sub_DEAFA(2)`). |
| 2 | `onResume` | `()I` | 0xEDDD8 | Thumb | Test resume lifecycle hook (`sub_DEAFA(1)`). |

### Class 2: `com/gamesafe/ano/AnoSdk` (11 methods, production interface)

Target class name dynamically constructed at runtime by `sub_1AB09C` @ 0x1AB09C via additive XOR decoding:
`unk_64D9C` (`com/gamesafe/ano`, key 0xC0) + `unk_60769` (`/`) + `unk_63E47` (`Ano`, key 0xC0) + `unk_65282` (`Sdk`, key 0xC0) = `"com/gamesafe/ano/AnoSdk"`.

The `JNINativeMethod` array is constructed at `init_array[0]` (`sub_EF18C` @ 0xEF18C) into global memory `dword_3D2074..3D20F4` (11 entries × 12 bytes = 132 bytes). Every native handler checks `dword_3D206C`; if non-zero, calls are routed to a secondary dispatch table (`*(dword_3D206C + offset)`):

| Slot | Method Name | Java Signature | Name Decryptor | Signature Decryptor / Source | Native Handler RVA | Secondary Hook Offset | Purpose |
|---|---|---|---|---|---|---|---|
| 0 | `init` | `(Ljava/lang/Object;)V` | `sub_380220(2970)` | `sub_1AB060()` (0x1AB060) | 0xEE134 | `+60` | Primary Java SDK bootstrap. |
| 1 | `setuserinfo` | `(Ljava/lang/Object;)V` | `sub_3807B4(2977)` | `sub_1AB06C()` (0x1AB06C) | 0xEE260 | `+64` | Ingests Java UserInfo; extracts integer & string fields via JNI reflection into 144-byte struct, passes to `sub_D8970`. |
| 2 | `setuserinfoex` | `(Ljava/lang/Object;)V` | `sub_3812DC(2991)` | `sub_1AB078()` (0x1AB078) | 0xEE470 | `+68` | Ingests extended UserInfo; extracts 9 fields via JNI into 212-byte struct, passes to `sub_D9230`. |
| 3 | `setgamestatus` | `(Ljava/lang/Object;)V` | `sub_37CFEC(3007)` | `sub_1AB084()` (0x1AB084) | 0xEE700 | `+72` | Ingests game scene/state; extracts field `"game_status"` (`sub_EF418(&unk_64339, 12)`), passes to `sub_D82AC`. |
| 4 | `getsdkantidata` | `(Ljava/lang/Object;)I` | `sub_37DCAC(3023)` | `sub_1AB090()` (0x1AB090) | 0xEE78C | `+76` | Ingests context object; extracts report buffer via `sub_D6AC0()`. |
| 5 | `setsenddatatosvrcb` | `(Ljava/lang/Object;)V` | `sub_37EA38(3040)` | `sub_37EA38(3140)` | 0xEE958 | `+76` (alt) | Registers server transmit callback object. |
| 6 | `senddatatosdk` | `([BI)V` | `sub_37FAF4(3061)` | `sub_37E30C(3131)` | 0xEE9FC | `+80` | Ingests byte array packet from server; invokes `sub_D72E0`. |
| 7 | `senddatatosvr` | `([BI)V` | `sub_3807B4(3077)` | `sub_37E30C(3131)` | 0xEEA70 | `+84` | Sends detection report buffer upstream to game server. |
| 8 | `onruntimeinfo` | `([BI)V` | `sub_381474(3093)` | `sub_37E30C(3131)` | 0xEEBC4 | `+88` | Client performance/runtime anomaly notification. |
| 9 | `hasMatchRate` | `(I)I` | `sub_37D184(3109)` | `sub_37DD78(3124)` | 0xEED1C | `+92` | Detection confidence query; aborts if `dword_3D206C == 0`. |
| 10 | `setappobject` | `(ILjava/lang/Object;)I` | Literal `"setappobject"` | Literal `"(ILjava/lang/Object;)I"` | 0xEEDB8 | `+96` | Generic Java object context setter (Activity / Application). |

## Key Pseudocode

### 1. JNI_OnLoad Registration Sequence (0xEEE94, from RAW/m1_asm_onload.txt & RAW/m1_asm_regnatives.txt)

```c
// JNI_OnLoad @ 0xEEE94
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if ( (*vm)->GetEnv(vm, (void**)&env, 0x10004) != JNI_OK || !env )
        return 0x10004;

    // 1. Register Class 1: com/tss/gamedemo/Game (3 methods)
    const char *class1_name = sub_37FD58(3164); // "com/tss/gamedemo/Game"
    jclass class1 = (*env)->FindClass(env, class1_name);
    if ( class1 && !(*env)->ExceptionCheck(env) ) {
        (*env)->RegisterNatives(env, class1, (JNINativeMethod*)0x3A7250, 3);
        (*env)->DeleteLocalRef(env, class1);
    } else {
        (*env)->ExceptionClear(env);
    }

    // 2. Register Class 2: com/gamesafe/ano/AnoSdk (11 methods)
    const char *class2_name = sub_1AB09C();     // "com/gamesafe/ano/AnoSdk"
    jclass class2 = (*env)->FindClass(env, class2_name);
    if ( class2 && !(*env)->ExceptionCheck(env) ) {
        (*env)->RegisterNatives(env, class2, (JNINativeMethod*)0x3D2074, 11);
        (*env)->DeleteLocalRef(env, class2);
    } else {
        (*env)->ExceptionClear(env);
    }

    sub_F11B0();  // Global env/state singleton allocation (188 bytes)
    sub_F18B4();
    return 0x10004; // JNI_VERSION_1_4
}
```

### 2. Runtime Class 2 Name Builder (`sub_1AB09C` @ 0x1AB09C)

```c
// sub_1AB09C @ 0x1AB09C (RAW/m1_asm_onload.txt:102-147)
const char *sub_1AB09C() {
    if ( unk_3D691C != 0 ) return unk_3D691C;

    char part1[18], part2[5], part3[5], full[128];
    sub_1AB88C(&unk_64D9C, 17, part1); // Key 0xC0 + i -> "com/gamesafe/ano"
    sub_1AB88C(&unk_63E47, 4,  part2); // Key 0xC0 + i -> "Ano"
    sub_1AB88C(&unk_65282, 4,  part3); // Key 0xC0 + i -> "Sdk"

    memset(full, 0, sizeof(full));
    sub_34F024(full, part1);       // "com/gamesafe/ano"
    sub_34F024(full, "/");         // Literal "/" @ 0x60769
    sub_34F024(full, part2);       // "Ano"
    sub_34F024(full, part3);       // "Sdk"
    unk_3D691C = sub_34F042(full); // Returns allocated string "com/gamesafe/ano/AnoSdk"
    return unk_3D691C;
}
```

### 3. JNI Native Method Table Builder (`sub_EF18C` @ 0xEF18C, `init_array[0]`)

```c
// sub_EF18C @ 0xEF18C (RAW/m2_c_EF18C.txt)
int sub_EF18C() {
    // JNINativeMethod layout: { const char *name, const char *signature, void *fnPtr }
    dword_3D2074 = sub_380220(2970); // "init"
    dword_3D2078 = sub_1AB060();     // "(Ljava/lang/Object;)V"
    dword_3D207C = (int)sub_EE134;

    dword_3D2080 = sub_3807B4(2977); // "setuserinfo"
    dword_3D2084 = sub_1AB06C();     // "(Ljava/lang/Object;)V"
    dword_3D2088 = (int)sub_EE260;

    dword_3D208C = sub_3812DC(2991); // "setuserinfoex"
    dword_3D2090 = sub_1AB078();     // "(Ljava/lang/Object;)V"
    dword_3D2094 = (int)sub_EE470;

    dword_3D2098 = sub_37CFEC(3007); // "setgamestatus"
    dword_3D209C = sub_1AB084();     // "(Ljava/lang/Object;)V"
    dword_3D20A0 = (int)sub_EE700;

    dword_3D20A4 = sub_37DCAC(3023); // "getsdkantidata"
    dword_3D20A8 = sub_1AB090();     // "(Ljava/lang/Object;)I"
    dword_3D20AC = (int)sub_EE78C;

    dword_3D20B0 = sub_37EA38(3040); // "setsenddatatosvrcb"
    dword_3D20B4 = sub_37EA38(3140); // "(Ljava/lang/Object;)V"
    dword_3D20B8 = (int)sub_EE958;

    dword_3D20BC = sub_37FAF4(3061); // "senddatatosdk"
    dword_3D20C0 = sub_37E30C(3131); // "([BI)V"
    dword_3D20C4 = (int)sub_EE9FC;

    dword_3D20C8 = sub_3807B4(3077); // "senddatatosvr"
    dword_3D20CC = sub_37E30C(3131); // "([BI)V"
    dword_3D20D0 = (int)sub_EEA70;

    dword_3D20D4 = sub_381474(3093); // "onruntimeinfo"
    dword_3D20D8 = sub_37E30C(3131); // "([BI)V"
    dword_3D20DC = (int)sub_EEBC4;

    dword_3D20E0 = sub_37D184(3109); // "hasMatchRate"
    dword_3D20E4 = sub_37DD78(3124); // "(I)I"
    dword_3D20E8 = (int)sub_EED1C;

    dword_3D20EC = (int)"setappobject";
    dword_3D20F0 = (int)"(ILjava/lang/Object;)I";
    dword_3D20F4 = (int)sub_EEDB8;
    return dword_3D20E4;
}
```

### 4. Primary Native SDK Init (`AnoSDKInit` @ 0xE6E04)

```c
// AnoSDKInit @ 0xE6E04 (RAW/m2_decomp_batch1.txt)
int AnoSDKInit(int game_id) {
    sub_DD960(game_id);          // Sets up core init struct and invokes sub_DBC9C
    sub_36570C(game_id > -1, 0); // Arms monitor module #0 ("monitor" sub_3653D4)
    return -1093166917;
}
```

## How it fires / Call Graph

```
[Game Engine / Java Framework]
  │
  ├─ System.loadLibrary("anogs")
  │    └─ dlopen("libanogs.so")
  │         ├─ init_array[0] (0xEF18C): Builds JNI table in dword_3D2074..3D20F4
  │         └─ 66 other init_array ctors: Singletons & atexit registrations
  │
  ├─ JNI_OnLoad @ 0xEEE94
  │    ├─ vm->GetEnv(&env, JNI_VERSION_1_4)
  │    ├─ FindClass("com/tss/gamedemo/Game") -> RegisterNatives(..., 0x3A7250, 3)
  │    ├─ sub_1AB09C() -> "com/gamesafe/ano/AnoSdk"
  │    ├─ FindClass("com/gamesafe/ano/AnoSdk") -> RegisterNatives(..., 0x3D2074, 11)
  │    └─ sub_F11B0() -> pthread_once state singleton (188 bytes)
  │
  ├─ Free Fire C# / Native Bootstrap calls AnoSDKInit(game_id) @ 0xE6E04
  │    ├─ sub_DD960(game_id) -> sub_DBC9C(ctx)   [CORE INIT & DETECTION ARMED]
  │    │    ├─ byte_3D2064 = 1
  │    │    ├─ sub_37C15C: Wires tss_sdk_send_data_to_svr callback (FF blocks on this!)
  │    │    ├─ sub_36C2C8: Spawns "ano_%d" worker threads (thread-driven scanners)
  │    │    └─ [failure branch] getpid(); kill(pid, 9);
  │    └─ sub_36570C(1, 0): Instantiates monitor module 0
  │
  ├─ Game Session Flow (Java -> JNI)
  │    ├─ com.gamesafe.ano.AnoSdk.setuserinfo(obj) -> sub_EE260 -> sub_D8970
  │    ├─ com.gamesafe.ano.AnoSdk.setgamestatus(obj) -> sub_EE700 -> sub_D82AC
  │    └─ com.gamesafe.ano.AnoSdk.senddatatosdk(bytes, len) -> sub_EE9FC -> sub_D72E0
  │
  └─ Telemetry Extraction Loop (Game Server / Network Service)
       ├─ AnoSDKGetReportData() @ 0xE8B4A -> sub_36570C(1, 4) + sub_D6AC0() [READ PACKET]
       ├─ Game sends report packet to server via UDP/TCP
       └─ AnoSDKDelReportData(ptr) @ 0xE9420 -> loc_D63B4(ptr) + sub_36570C(1, 5) [FREE PACKET]
```

## Divergence from the arm64 notes

1. **Class 2 Dynamic Construction Revealed**:
   - `INFO/ace_anticheat_notes/66_libanogs_jni_native_api.md` stated that Class 2's name was unknown, built dynamically to evade static analysis, and speculated names like `com.ace.AntiCheatExpert` or `com.tencent.GameProtect`.
   - **OUR PROVEN FINDING**: In our 32-bit v7a binary, `sub_1AB09C` @ 0x1AB09C directly constructs `com/gamesafe/ano/AnoSdk` by concatenating decoded chunks `com/gamesafe/ano` (0x64D9C), `/` (0x60769), `Ano` (0x63E47), and `Sdk` (0x65282).
2. **JNI Signatures Fully Resolved**:
   - Note 66 left methods 0–4 with `(?)` signatures, assuming separate helper functions `sub_2DC3AC..sub_2DC3DC` needed manual extraction.
   - **OUR PROVEN FINDING**: Methods 0, 1, 2, and 3 have identical signature `(Ljava/lang/Object;)V` (returned by plaintext helpers `sub_1AB060..sub_1AB084`); method 4 has signature `(Ljava/lang/Object;)I` (`sub_1AB090`).
3. **Secondary Dispatch Table Hook (`dword_3D206C`)**:
   - The arm64 notes do not identify the `dword_3D206C` dynamic dispatch pointer present in our v7a build. In our binary, every single `sub_EE*` native handler branches through `*(dword_3D206C + offset)` if `dword_3D206C != 0`.
4. **Export Set Expansion**:
   - Note 66 references a generic 11-method JNI registration. Our v7a dynamic export table exposes 21 distinct C symbols, including tiered reporting functions (`AnoSDKGetReportData2/3/4` and `AnoSDKDelReportData3/4`).
5. **Base Offsets Shift**:
   - `AnoSDKInit`: arm64 0x1DA368 vs v7a 0xE6E04.
   - `JNI_OnLoad`: arm64 0x1E2444 vs v7a 0xEEE94.
   - JNI table builder: arm64 `init_ctor_02` vs v7a `init_array[0]` (`sub_EF18C` @ 0xEF18C).

## Bypass Implications

1. **Static Hooking of `AnoSDKInit` is Fatal (PROVEN)**:
   - Neutering `AnoSDKInit` @ 0xE6E04 with `return 0` deadlocks the Free Fire boot sequence at resource chunk 1 (ANR). Free Fire explicitly awaits the `tss_sdk_send_data_to_svr` callback registered inside `sub_DBC9C` / `sub_37C15C`.
   - **Requirement**: `AnoSDKInit` must execute normally and remain alive.
2. **Runtime Java Surface Target Identified (PROVEN)**:
   - Any Java-level instrumentation (Xposed, Frida, LSPosed) intended to monitor or suppress anti-cheat calls must hook `com.gamesafe.ano.AnoSdk`, NOT hypothetical Tencent or ACE classes.
3. **Telemetry Eavesdropping at Native Export Level (PROVEN)**:
   - `AnoSDKGetReportData` @ 0xE8B4A and `AnoSDKDelReportData` @ 0xE9420 are exported C functions with non-mangled names. Placing an inline hook on `AnoSDKGetReportData` allows us to inspect, copy, or zero out the anti-cheat report buffers before they are handed to the network layer.
4. **Secondary Dispatch Hijack (`dword_3D206C`) (HYPOTHESIS)**:
   - Because all 11 native methods check `if (dword_3D206C != 0) return (*(dword_3D206C + offset))(...)`, setting `dword_3D206C` to point to a custom function table could redirect all incoming Java calls without modifying read-only code segments (avoiding `.text` checksum detection). Needs runtime verification.

## Open questions / next probes

1. **Verify `dword_3D206C` Runtime Origin**:
   - Run `analysis\tools\ida.cmd libanogs search RAW\m1_3d206c_callers.json callers 0x3D206C` or inspect cross-references to identify which function writes to `dword_3D206C` (is it populated by `libanort.so` via ioctl?).
2. **Capture Live Report Packet from `AnoSDKGetReportData`**:
   - Hook `AnoSDKGetReportData` @ `0xE8B4A` via Frida to dump the memory buffer returned by `sub_D6AC0()` and observe whether it matches the `COREREPORT` telemetry structure described in `04_detection_targets.md`.
3. **Trace `AnoSDKOnRecvSignature` Caller**:
   - Determine whether the game client or an external server ticket calls `AnoSDKOnRecvSignature` @ `0xEC996` during APK verification at startup.
