import io, sys, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)


def hexb(hx):
    return bytes(int(hx[i:i+2], 16) for i in range(0, len(hx), 2))


def static_xor(b):
    return bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(b))


def parse_arrays(s):
    out = {}
    for m in re.finditer(r':array_(\w+)\s*\n(.*?)\n\s*\.end array-data', s, re.S):
        vals = re.findall(r'0x([0-9a-fA-F]{1,2})t', m.group(2))
        if vals:
            out[m.group(1)] = ''.join(v.zfill(2) for v in vals)
    return out


def hexkey_from(a16):
    return static_xor(hexb(base64.b64decode(hexb(a16)).decode('latin1')))


def decrypt(dhex, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(hexb(dhex)))


# ---- 弃我去者昨日之日不可留 (media/download class) in classes3 ----
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\com\Sx2\Team\Ban\君不见高堂明镜悲白发弃我去者昨日之日不可留َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if not m:
        continue
    a = parse_arrays(part)
    fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', part)
    # group fills into pairs (key,data) with the standard K(32hex),D pattern
    pairs = []
    i = 0
    while i + 1 < len(fills):
        k, d = fills[i], fills[i + 1]
        if len(a.get(k, '')) == 32:
            pairs.append((k, d))
            i += 2
        else:
            i += 1
    vals = []
    for k, d in pairs:
        try:
            vals.append(decrypt(a[d], hexkey_from(a[k])))
        except Exception:
            vals.append(b'<err>')
    if vals:
        print('== %s ==' % m.group(1))
        for k, d, v in [(k, d, None) for k, d in pairs]:
            pass
        for v in vals:
            print('   ', repr(v))
