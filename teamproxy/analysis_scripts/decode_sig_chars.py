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


def hexkey_string(array_hex):
    """standard 16B ascii-b64 -> base64 decode -> text(hex) -> static XOR -> key bytes -> decode latin1"""
    return static_xor(hexb(base64.b64decode(hexb(array_hex)).decode('latin1'))).decode('latin1')


def xorsingle(cipher_byte, keystr):
    return bytes([cipher_byte ^ ord(keystr[0])])


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)

for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if not m or m.group(1) != '请君为我倾耳听':
        continue
    a = parse_arrays(part)
    # Read method code lines to map sequence of key arrays to cipher bytes
    lines = part.split('\n')
    print('==== 请君为我倾耳听 ====')
    # Track flow: for each new-array of size 1 w/ aput-byte value X -> fill key array above it
    # simpler: simulate: for each 'fill-array-data ... :array_N' where array_N 32hex -> produce keystr;
    # look for the following aput-byte vX, 0xNN (before next fill key) => cipher byte
    keyfill = None
    keystr = None
    i = 0
    for i, line in enumerate(lines):
        fm = re.search(r'fill-array-data\s+v\d+,\s*:array_(\w+)', line)
        if fm:
            lab = fm.group(1)
            if len(a.get(lab, '')) == 32:
                keystr = hexkey_string(a[lab])
                # next cipher byte = aput-byte const
                continue
        am = re.search(r'aput-byte\s+v\d+,\s*v\d+,\s*(\S+)', line)
        if am and keystr:
            val = am.group(1)
            if val.startswith('0x'):
                b = int(val, 16)
                ch = bytes([b ^ ord(keystr[0])])
                print('  key %r byte %02x -> %r (%s)' % (keystr, b, ch, ch.decode('latin1')))
            keystr = None
