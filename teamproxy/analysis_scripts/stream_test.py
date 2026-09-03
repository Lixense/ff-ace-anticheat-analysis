import io, sys, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)

data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()
blob = data[0x1bf00:0x1e800]

def printable_ratio(b):
    if not b: return 0
    return sum(1 for c in b if 32 <= c < 127 or c in (9,10,13)) / len(b)

# candidate keystreams
cands = {
    'arabic_low': KEYB,
    'arabic_utf16le': KEY.encode('utf-16-le'),
    'Sx2TeamAppSecureKey2026@!': b'Sx2TeamAppSecureKey2026@!',
    'SX2-TEAM-HAW8E0RP': b'SX2-TEAM-HAW8E0RP',
    'SX2': b'SX2',
    'sx2': b'sx2',
    'Sx2': b'Sx2',
    'naga': b'naga',
}
for name, ks in cands.items():
    out = bytes(blob[k] ^ ks[k % len(ks)] for k in range(len(blob)))
    pr = printable_ratio(out)
    print('%s: printable ratio %.3f' % (name, pr))
    if pr > 0.5:
        # find printable runs
        runs = re.findall(rb'[\x20-\x7e]{8,}', out)
        for r in runs[:20]:
            print('   ', r)
