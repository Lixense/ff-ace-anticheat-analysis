import io, sys, re, base64, hashlib

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


def key_from(hk):
    return static_xor(hexb(base64.b64decode(hexb(hk)).decode('latin1')))


def xorb(data, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(data))


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()

# Whole-file arrays
a = parse_arrays(s)
print('whole-file arrays:', {k: len(v) for k, v in a.items()})

# But fills repeat labels per method. Instead locate the two 16-byte ciphertexts by scanning fills of
# the 请君为我倾耳听 method region and pairing as they appear with their immediately preceding 32-hex key
parts = re.split(r'(?=\.method )', s)
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if not m or m.group(1) not in ('请君为我倾耳听', '钟鼓馔玉不足贵'):
        continue
    pa = parse_arrays(part)
    fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', part)
    print('== %s fills: %s' % (m.group(1), fills))
    print('   lens: %s' % {f: len(pa[f]) for f in fills})
