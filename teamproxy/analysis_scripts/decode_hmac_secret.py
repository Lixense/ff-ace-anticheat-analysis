import io, sys, os, re, base64, itertools

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)


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
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(hexb(hexdata)))


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
arrays = parse_arrays(s)
print('arrays:', {k: len(v) for k, v in arrays.items()})
# method 请君为我倾耳听 contains the HmacSHA256 secret building: find its part
parts = re.split(r'(?=\.method )', s)
for part in parts:
    if '请君为我倾耳听' not in part.split('(')[0][:200]:
        continue
    a = parse_arrays(part)
    fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', part)
    print('method 请君为我倾耳听 fills:', fills)
    for lab in a:
        if len(a[lab]) <= 64 and len(a[lab]) > 4:
            print('  arr', lab, a[lab], '-> main key:', repr(decrypt(a[lab], key_from([k for k in a if len(a[k])==32][0])) if any(len(a[k])==32 for k in a) else b''))
