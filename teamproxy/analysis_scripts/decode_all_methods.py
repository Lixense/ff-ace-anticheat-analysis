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


def walk_clinit(s):
    """parse clinit; pair arrays sequentially key(32 hex) then data"""
    cl = re.search(r'\.method static constructor <clinit>.*?\.end method', s, re.S)
    if not cl:
        return []
    arrays = parse_arrays(cl.group(0))
    # order of appearance
    order = [lab for lab in re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', cl.group(0))]
    out = []
    i = 0
    while i + 1 < len(order):
        k, d = order[i], order[i + 1]
        if len(arrays.get(k, '')) == 32:
            try:
                out.append(decrypt(arrays[d], key_from(arrays[k])))
            except Exception:
                out.append(b'<err>')
            i += 2
        else:
            i += 1
    return out


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发千磨万击还坚韧任尔东西南北风َ.smali'
s = open(p, encoding='utf-8').read()
# decode all method-level string pairs too: every method body with fills where first array is 32 hex
# collect arrays across whole file
arrays_all = parse_arrays(s)
# method split by '.method'
parts = re.split(r'(?=\.method )', s)
for part in parts:
    if '.method' not in part:
        continue
    mname = re.match(r'\.method (?:public|private|protected|static)?\s*(?:static\s*)?([\w<>]+)\(', part)
    arrs_in = parse_arrays(part)
    fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', part)
    vals = []
    i = 0
    while i + 1 < len(fills):
        k, d = fills[i], fills[i + 1]
        if len(arrs_in.get(k, '')) == 32:
            try:
                vals.append(decrypt(arrs_in[d], key_from(arrs_in[k])))
            except Exception:
                vals.append(b'<err>')
            i += 2
        else:
            i += 1
    if vals:
        print('== method', mname.group(1) if mname else '?')
        for v in vals:
            print('   ', v)
