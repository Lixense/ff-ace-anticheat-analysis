import io, sys, os, re, base64, glob

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


def decode_pairs(text):
    a = parse_arrays(text)
    fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', text)
    out = []
    i = 0
    while i + 1 < len(fills):
        k, d = fills[i], fills[i + 1]
        if len(a.get(k, '')) == 32:
            try:
                out.append(decrypt(a[d], hexkey_from(a[k])))
            except Exception:
                out.append(b'<err>')
            i += 2
        else:
            i += 1
    return out


out_lines = []
seen = set()
for pat in [r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\com\Sx2\Team\Ban\*.smali',
            r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\*.smali',
            r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes5\com\Sx2\Team\Ban\*.smali']:
    for p in glob.glob(pat):
        b = os.path.basename(p)
        if b in seen:
            continue
        seen.add(b)
        s = open(p, encoding='utf-8').read()
        parts = re.split(r'(?=\.method )', s)
        vals = []
        for part in parts:
            vals += decode_pairs(part)
        if vals:
            out_lines.append('## ' + b)
            for v in vals[:80]:
                out_lines.append('    %r' % v)
with open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decoded_more.txt', 'w', encoding='utf-8') as fh:
    fh.write('\n'.join(out_lines))
print('wrote', len(out_lines), 'lines')
