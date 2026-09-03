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


def key_bytes_from(array16_hex):
    """array16 = ascii base64 text bytes -> base64 decode -> text hex -> static-xor -> key bytes"""
    return static_xor(hexb(base64.b64decode(hexb(array16_hex)).decode('latin1')))


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if not m or m.group(1) != '请君为我倾耳听':
        continue
    a = parse_arrays(part)
    # From source:
    # array_0 -> key; 1-byte 0x18 ^ key[0]? then p2
    # Actually smali: 1-byte array [0x18], key array_0 -> 奔流到海不复回([B,Str,ZZ) = XOR bytes with key STRING
    # key string from array_0 after full pipeline is the 'hex key str'?? Wait no: array_0 flow:
    #   fill array_0 -> b64 -> 'hex string s' -> 君不见...  (hex decode + static xor) => key k
    # So v1 = key string k. Then [0x18] XOR k => single char.
    for i, lab in enumerate(['0', '1', '2', '3']):
        k = key_bytes_from(a[lab])
        print('array_%s key bytes: %r' % (lab, k))
    # cipher bytes in order: 0x18 (first, before p2), 0x18 (second, before p3), 0x49 (before p4/p5 J)
    for ciph in (0x18, 0x18, 0x49):
        pass
