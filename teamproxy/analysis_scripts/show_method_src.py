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


def key_from(hk):
    return static_xor(hexb(base64.b64decode(hexb(hk)).decode('latin1')))


def xorb(data, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(data))


def dec_pair(data_hex, key_hex):
    return xorb(hexb(data_hex), key_from(key_hex))


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if not m or m.group(1) not in ('请君为我倾耳听', '钟鼓馔玉不足贵'):
        continue
    pa = parse_arrays(part)
    # identify: keys are 32-hex arrays. The method decrypt flow appears:
    # arrayK1->dec->key; arrayD1 xor -> str; arrayK2->dec->key; arrayD2 xor -> str...
    # so fills alternate K,D,K,D when K is 32 hex.
    fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', part)
    keys = [f for f in fills if len(pa.get(f, '')) == 32]
    datas = [f for f in fills if f not in keys]
    print('== %s keys=%s datas=%s' % (m.group(1), keys, datas))
    # The order in smali should interleave; emulate by reading actual code segment
    print(part[:2000])
