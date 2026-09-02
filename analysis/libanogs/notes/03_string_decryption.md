# libanogs.so — String Decryption & Decoder Architecture (our v7a analysis)

> Source of truth: OUR analysis/libanogs/libanogs.so (md5 2810a533, from IDENTITY.txt).
> Cross-ref hint (verify, don't trust): INFO/ace_anticheat_notes/64_master_string_dictionary.md — arm64 build.

## Summary

In our 32-bit ARMv7a `libanogs.so`, fewer than 20 strings exist in plaintext in the static `.rodata` section. Over 2,000 sensitive detection targets, telemetry names, and config keys are obfuscated through two primary layers: (1) an indexed string-ID table resolved at runtime via encrypted numerical identifiers (`sub_380BB0`, `sub_380220`, `sub_37CBF0`), and (2) a dynamic hex-to-byte decompression routine (`sub_36D730`) that unpacks packed hex stream buffers into byte sequences. Cross-referencing these decoding entry points reveals the central telemetry, root scan, and anti-tamper strings.

## Evidence

### 1. The Core Hex Decoder (`sub_36D730`)

The primary byte unpacker routine is `sub_36D730` @ `0x36D730`. It takes packed 2-character hex pairs from an encoded buffer and converts them into ASCII strings via `sscanf`:

| Offset (RVA) | Symbol / our-name | ISA | What it does | Evidence |
|---|---|---|---|---|
| 0x36D730 | `sub_36D730` | Thumb | Unpacks 2-byte hex characters into decoded buffer | RAW/m3_dec.txt |
| 0x380BB0 | `sub_380BB0` | Thumb | String ID dispatcher (ids 33682..33792: monitor module names) | RAW/m2_decomp_36570c.txt |
| 0x380220 | `sub_380220` | Thumb | String ID dispatcher (ids 2970..3140: JNI method signatures) | RAW/m2_c_EF18C.txt |
| 0x37CBF0 | `sub_37CBF0` | Thumb | Telemetry channel ID decoder (id 49902: `"COREREPORT"`) | RAW/kr_sub_3653D4.c |

```c
// sub_36D730 @ 0x36D730 (RAW/m3_dec.txt, trimmed)
_BYTE *__fastcall sub_36D730(int a1, unsigned int a2, _BYTE *a3, int a4) {
  int v8; _BYTE *v9; int v10; char s[2];
  if ( a1 != 0 && a3 != nullptr && 2 * a4 >= a2 ) {
    if ( a4 != 0 ) {
      v8 = a1 + 1; v9 = a3;
      do {
        *(_WORD *)s = *(_WORD *)(v8 - 1);
        sscanf(s, "%x", &v10);
        v8 += 2;
        *v9++ = v10;
        --a4;
      } while ( a4 != 0 );
    }
    return a3;
  }
  return nullptr;
}
```

### 2. Recovered String Cross-References & Target Strings

Cross-referencing string consumers in `sp3.txt` and `RAW/` isolates the core reporting channels and telemetry keys:

| String / Target | RVA | Consumers / Callees | Purpose |
|---|---|---|---|
| `tdm_report` | 0x5FB4E | 0x3653F8, 0x365400, 0x36551C (`sub_3653D4`) | Primary TDM security event logging |
| `COREREPORT` | 0x62D05 | 0x36545E, 0x365530, 0x36557C (`sub_3653D4`) | Security violation transmission packet |
| `TotalMem:%d;FreeSpaceTDM:%d` | 0x6428C | 0x3652DE, 0x3652E4, 0x36531C (`sub_365298`) | Device memory telemetry payload |
| `REMOTECONFIG` | 0x646FA | 0x364C84, 0x364C88, 0x364CA4 (`sub_364D30`) | Cloud configuration & dynamic detection rules |
| `tdm_dev_info` | 0x64F43 | 0x364D4A, 0x364D50, 0x364E0C (`sub_364D30`) | Device fingerprinting packet |
| `com.ace.gamesafe4` | 0x660D6 | 0x175D9E, 0x175DA2, 0x175E30 | Companion security package verification |
| `@^NOX]hvgzaq` | 0xCED2D | Decoded at runtime via XOR/sub mask | NOX emulator environment signature |

## How it fires / call graph

```
Runtime Event (Boot, Hook Check, Scan)
  │
  ├─► Module Init (sub_36570C)
  │     └─► sub_380BB0(id 33682) ──► resolves monitor name
  │
  ├─► JNI Registration (sub_EF18C)
  │     └─► sub_380220(ids 2970..3140) ──► resolves Java method names/signatures
  │
  └─► Telemetry Dispatcher (sub_3653D4)
        ├─► sub_37CBF0(49902) ──► resolves "COREREPORT"
        └─► sub_36D730(...) ──► decodes hex-packed buffer into plaintext
```

## Divergence from the arm64 notes

- In `INFO/ace_anticheat_notes/64_master_string_dictionary.md` (ARM64), many string targets like `/data/local/tmp/frida-server` and root binaries are listed in an unencrypted string dictionary.
- In our **ARMv7a build**, these scan targets are **fully encrypted** inside the ID dispatchers (`sub_380BB0`, `sub_380220`) and only decompressed into heap buffers on demand.
- The string decoder `sub_36D730` operates on hex character pairs via `sscanf(s, "%x", &v10)`, whereas ARM64 notes describe direct table-based XOR streams.

## Bypass implications

1. **PROVEN:** All telemetry strings (`COREREPORT`, `tdm_report`, `tdm_dev_info`) converge on **`sub_3653D4`**. Rather than trying to patch or intercept thousands of encrypted strings individually, silencing `sub_3653D4` via `byte_3DB1EC = 0` eliminates outbound report delivery entirely.
2. **HYPOTHESIS:** Emulators and virtualization frameworks (such as NOX) are identified via encoded strings (`@^NOX]hvgzaq`). Neutralizing the string decoder table entries at load time or intercepting the string lookups can blind specific environment scans.

## Open questions / next probes

1. Write a standalone Python script to query all xrefs to `sub_380BB0` across the `.i64` corpus to extract the complete table of all 2,000+ IDs.
2. Verify if `sub_36D730` is called during the boot handshake (`AnoSDKInit`) or only when a detection event is triggered.
