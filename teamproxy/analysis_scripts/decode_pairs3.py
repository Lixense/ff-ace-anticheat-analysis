import io, sys, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

def key_from_b64keyarr(arr16):
    """16 ascii b64 bytes -> b64decode -> hex text -> hex decode -> XOR arabic low bytes"""
    hexstr = base64.b64decode(arr16).decode('latin1')
    raw = bytes.fromhex(hexstr)
    return bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(raw))

def dec(ct, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(ct))

pairs = [
    ('c15e', 0x1c15e, 'c16e', 0x1c16e, 5),
    ('c177', 0x1c177, 'c187', 0x1c187, 8),
    ('c193', 0x1c193, 'c1a3', 0x1c1a3, 27),
]
for kn, ka, cn, ca, clen in pairs:
    key = key_from_b64keyarr(data[ka:ka+16])
    ct = data[ca:ca+clen]
    print('%s key=%s | %s ct=%s -> %r' % (kn, key.hex(), cn, ct.hex(), dec(ct, key)))
