import io, sys, os, re, base64

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


def decode_pairs_in(text):
    """Scan text for key(32 hex)+data pairs by array usage order"""
    arrays = parse_arrays(text)
    fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', text)
    out = []
    i = 0
    while i + 1 < len(fills):
        k, d = fills[i], fills[i + 1]
        if len(arrays.get(k, '')) == 32:
            try:
                out.append(decrypt(arrays[d], key_from(arrays[k])))
            except Exception:
                out.append(b'<err>')
            i += 2
        else:
            i += 1
    return out


BASE = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled'
import glob
targets = []
for dex in ['smali_classes3', 'smali_classes4', 'smali_classes5']:
    targets += glob.glob(os.path.join(BASE, dex, 'com', 'Sx2', 'Team', 'Ban', '*.smali'))
with open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decoded_strings.txt', 'w', encoding='utf-8') as fh:
    for p in sorted(targets):
        s = open(p, encoding='utf-8').read()
        for m in re.finditer(r'\.method\s+((?:public|private|protected|static|final|synthetic|bridge|\s)*?)([\w<>]+)\([^)]*\)', s):
            # just decode whole file pairs per method chunk
            pass
        # decode per method for locality
        parts = re.split(r'(?=\.method )', s)
        fh.write('===== %s =====\n' % os.path.basename(p))
        for part in parts:
            if '.method' not in part:
                continue
            vals = decode_pairs_in(part)
            if vals:
                mm = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
                fh.write('-- method %s --\n' % (mm.group(1) if mm else '?'))
                for v in vals:
                    fh.write('    %r\n' % v)
print('done -> decoded_strings.txt')
