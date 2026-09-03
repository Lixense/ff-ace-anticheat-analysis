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


def hexkey_from(array16):
    """16B ascii-b64 -> text -> static-xor -> key bytes"""
    return static_xor(hexb(base64.b64decode(hexb(array16)).decode('latin1')))


def decrypt(data_hex, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(hexb(data_hex)))


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)
for part in parts:
    if '<clinit>' not in part:
        continue
    a = parse_arrays(part)
    fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', part)
    print('fills order:', fills)
    pairs = []
    i = 0
    while i + 1 < len(fills):
        k, d = fills[i], fills[i + 1]
        if len(a.get(k, '')) == 32:
            pairs.append((k, d))
            i += 2
        else:
            i += 1
    for k, d in pairs:
        try:
            res = decrypt(a[d], hexkey_from(a[k]))
            print('array_%s+array_%s -> %r' % (k, d, res))
        except Exception as e:
            print('array_%s+array_%s ERR %s' % (k, d, e))
