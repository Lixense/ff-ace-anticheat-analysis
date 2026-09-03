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


def key_from(a):
    return static_xor(hexb(base64.b64decode(hexb(a)).decode('latin1')))


def decrypt(dhex, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(hexb(dhex)))


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\com\Sx2\Team\Ban\君不见高堂明镜悲白发弃我去者昨日之日不可留َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if not m:
        continue
    a = parse_arrays(part)
    fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', part)
    # Strict interleaved key/data — but a few fills may not follow the pattern (e.g., extra consts).
    # Decode only when array fits the key pattern: the KEY arrays here are 32 hex (16 bytes) OR the key can be shorter...
    # Test: try treating each pair strictly even/odd:
    vals = []
    for i in range(0, len(fills) - 1, 2):
        k, d = fills[i], fills[i + 1]
        try:
            v = decrypt(a[d], key_from(a[k]))
            vals.append(v)
        except Exception:
            vals.append(b'<err:%s,%s>' % (k.encode(), d.encode()))
    if vals:
        print('== %s ==' % m.group(1))
        for v in vals:
            print('   ', repr(v))
