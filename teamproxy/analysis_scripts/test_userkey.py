import io, sys, os, re, base64

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


# The garbage pairs from API activity method 请君为我倾耳听 and 钟鼓馔玉不足贵:
# Pairing by order of fills in those methods: key arrays are the 32-hex-char(16B) ones.
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)
targets = []
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if m and m.group(1) in ('请君为我倾耳听', '钟鼓馔玉不足贵'):
        a = parse_arrays(part)
        fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', part)
        pairs = []
        i = 0
        while i + 1 < len(fills):
            k, d = fills[i], fills[i + 1]
            if len(a.get(k, '')) == 32:
                pairs.append((k, d))
                i += 2
            else:
                i += 1
        targets.append((m.group(1), a, pairs))

# Test candidate keys against the data arrays: main-derived key, and user key (utf8/latin1/utf16)
for name, a, pairs in targets:
    print('==== %s ====' % name)
    for k, d in pairs:
        data_hex = a[d]
        try:
            k1 = key_from(a[k])
        except Exception as e:
            k1 = b''
        cands = {
            'main_key': k1,
            'userkey_utf8': USERKEY.encode('utf-8'),
            'userkey_latin1': USERKEY.encode('latin1'),
            'userkey_utf16le': USERKEY.encode('utf-16-le'),
        }
        # add hash/hex variants
        import hashlib
        cands['md5(userkey)'] = hashlib.md5(USERKEY.encode()).digest()
        cands['sha1(userkey)'] = hashlib.sha1(USERKEY.encode()).digest()
        cands['hex(md5)'] = hashlib.md5(USERKEY.encode()).hexdigest().encode()
        cands['hex(sha256)'] = hashlib.sha256(USERKEY.encode()).hexdigest().encode()
        print('-- pairs %s/%s data_len=%d' % (k, d, len(data_hex) // 2))
        for cn, ck in cands.items():
            r = decrypt(data_hex, ck)
            if printable(r) and len(r) > 1:
                print('   [%s] %r' % (cn, r))
        # also data via main key then user key
        try:
            base = decrypt(data_hex, key_from(a[k]))
            for cn, ck in cands.items():
                r = bytes(c ^ ck[i % len(ck)] for i, c in enumerate(base))
                if printable(r) and len(r) > 1:
                    print('   [double %s] %r' % (cn, r))
        except Exception:
            pass
