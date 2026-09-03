import io, sys, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

def arabic_xor_hexstr(hexstr):
    return bytes(int(hexstr[i:i+2],16) ^ KEYB[i % len(KEYB)] for i in range(0, len(hexstr), 2))

def b64str(arr):
    return base64.b64decode(arr).decode('latin1')

def dec(ct, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(ct))

def entry(addr16):
    """Given file addr of a 16B b64 key array -> key bytes"""
    return arabic_xor_hexstr(b64str(data[addr16:addr16+16]))

# decode all onCreate (0x31198) strings
pairs = [
    ('c15e(16B key)', 0x1c15e, 'c16e(5B ct)', 0x1c16e, 5),
    ('c177(16B key)', 0x1c177, 'c187(8B ct)', 0x1c187, 8),
    ('c193(16B key)', 0x1c193, 'c1a3(27B ct)', 0x1c1a3, 27),
]
for kn, ka, cn, ca, clen in pairs:
    key = entry(ka)
    ct = data[ca:ca+clen]
    print('%s key=%s | %s ct=%s -> %r' % (kn, key.hex(), cn, ct.hex(), dec(ct, key)))

# c18f 4B = 'NDU=' -> base64 of '5'? or a partial
c18f = data[0x1c18f:0x1c18f+4]
print('c18f raw=%s b64dec=%r' % (c18f, base64.b64decode(c18f + b'='*((-len(c18f))%4))))
