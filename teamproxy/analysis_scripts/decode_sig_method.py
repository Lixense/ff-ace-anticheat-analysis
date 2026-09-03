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


def get_hexkey(array_hex):
    """16 ascii bytes -> base64 -> hex text -> static-xor -> HEX STRING (the actual key string)"""
    return static_xor(hexb(base64.b64decode(hexb(array_hex)).decode('latin1'))).decode('latin1')


def xor_single_byte(byteval, hexkeystr):
    k = bytes.fromhex(hexkeystr) if False else hexkeystr
    # In smali: byte (int) xor charAt(idx) — char = 16bit; they then int-to-byte.
    # The key string here is the hex key. We'll XOR 0x18 with the FIRST char of hex key string? 
    # Actually usage: 1-byte cipher C, key string S: byte ^ S.charAt(i%len)
    return bytes([byteval ^ ord(hexkeystr[0 % len(hexkeystr)])])


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if not m or m.group(1) not in ('请君为我倾耳听', '钟鼓馔玉不足贵'):
        continue
    a = parse_arrays(part)
    print('==== %s ====' % m.group(1))
    print('arrays:', {k: a[k] for k in a})
    # keys are the 32-hex (16B) arrays: they produce hex key strings
    for lab in a:
        if len(a[lab]) == 32:
            try:
                print('  array %s -> hexkey str: %r' % (lab, get_hexkey(a[lab])))
            except Exception as e:
                print('  array %s err %s' % (lab, e))
