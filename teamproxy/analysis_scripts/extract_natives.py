import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()

targets = [0x2f780, 0x31198, 0x3914c, 0x40ff4, 0x46fbc, 0x60ee4, 0x6c528, 0x276b8, 0x276bc]

# FUN headers look like: /* ===== FUN_00126ca0 @ 00126ca0 ==== */
# find each function whose address matches (case-insensitive hex)
for t in targets:
    pat = '@ %08x ' % t
    idx = s.find(pat)
    if idx < 0:
        # try without leading zeros
        pat2 = '@ %x ' % t
        idx = s.find(pat2)
    if idx < 0:
        print('### 0x%x NOT FOUND in decompiled output' % t)
        continue
    # back up to header start
    hdr = s.rfind('/* =====', 0, idx)
    # find function end = next /* ===== */
    end = s.find('/* =====', idx + 10)
    body = s[hdr:end if end > 0 else hdr + 8000]
    print('### 0x%x function (%d bytes):' % (t, len(body)))
    print(body[:7000])
    print()
