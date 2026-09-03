import io, sys, os, re, base64, hashlib, itertools

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)
USERKEY = 'SX2-TEAM-HAW8E0RP'


def hexb(hx):
    return bytes(int(hx[i:i+2], 16) for i in range(0, len(hx), 2))


def static_xor(b):
    return bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(b))


def parse_arrays(smali_text):
    out = {}
    for m in re.finditer(r':array_(\w+)\s*\n(.*?)\n\s*\.end array-data', smali_text, re.S):
        lab = m.group(1)
        body = m.group(2)
        vals = re.findall(r'0x([0-9a-fA-F]{1,2})t', body)
        if vals:
            out[lab] = ''.join(v.zfill(2) for v in vals)
    return out


def key_from(hexkey):
    kb = hexb(hexkey)
    hexstr = base64.b64decode(kb).decode('latin1')
    return static_xor(hexb(hexstr))


def decrypt(hexdata, key):
    if not key:
        return b''
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(hexb(hexdata)))


def printable(b):
    return all(32 <= x < 127 or x in (9, 10, 13) for x in b)


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)

# Collect the two garbage ciphertexts (16 bytes each): from '请君为我倾耳听' first two pairs
ciphs = []
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if m and m.group(1) == '请君为我倾耳听':
        a = parse_arrays(part)
        fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', part)
        for i in range(0, len(fills) - 1, 2):
            k, d = fills[i], fills[i + 1]
            if len(a.get(k, '')) == 32 and len(a.get(d, '')) == 32:
                ciphs.append((k, d, a[k], a[d]))

print('cipher pairs:', [(k, d) for k, d, _, _ in ciphs])

# candidate second keys
cands = {
    'userkey': USERKEY.encode('utf-8'),
    'userkey_hex': USERKEY.encode('utf-8').hex().encode(),
    'md5hex': hashlib.md5(USERKEY.encode()).hexdigest().encode(),
    'sha1hex': hashlib.sha1(USERKEY.encode()).hexdigest().encode(),
    'sha256hex': hashlib.sha256(USERKEY.encode()).hexdigest().encode(),
    'md5': hashlib.md5(USERKEY.encode()).digest(),
    'b64_userkey': base64.b64encode(USERKEY.encode()),
    'SX2TEAMHAW8E0RP': 'SX2TEAMHAW8E0RP'.encode(),
    'HAW8E0RP': 'HAW8E0RP'.encode(),
    'userkey_lower': USERKEY.lower().encode(),
}
# add user_key from prefs (same as USERKEY), api_key_free might be second key
cands['api_key_free'] = b'SX2-FREE-SECURE-2026-A7B8C9D0E1F2G3H4I5J6K7L8M9N0O1P2Q3R4S5T6U7V8W9X0Y1Z2'
cands['api_key_free_short'] = b'SX2-FREE-SECURE-2026'

for k, d, hk, hd in ciphs:
    mk = key_from(hk)
    c0 = hexb(hd)
    # what if data is XOR with mk then XOR with cand (either order), then must be printable ascii/b64
    print('== pair %s/%s ==' % (k, d))
    for cn, ck in cands.items():
        # order 1: xor mk then cand
        r1 = bytes(x ^ mk[i % len(mk)] for i, x in enumerate(c0))
        r1b = bytes(x ^ ck[i % len(ck)] for i, x in enumerate(r1))
        # order 2: xor cand then mk
        r2 = bytes(x ^ ck[i % len(ck)] for i, x in enumerate(c0))
        r2b = bytes(x ^ mk[i % len(mk)] for i, x in enumerate(r2))
        for nm, r in (('mk->cand', r1b), ('cand->mk', r2b)):
            if printable(r) and len(r) >= 4:
                print('   [%s %s] %r' % (cn, nm, r))
            # maybe result is b64-able to text
            if len(r) % 4 == 0:
                try:
                    d2 = base64.b64decode(r)
                    if printable(d2):
                        print('   [%s %s b64] %r' % (cn, nm, d2))
                except Exception:
                    pass
