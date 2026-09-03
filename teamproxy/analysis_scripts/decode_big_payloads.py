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


def key_from_hexarray(a16):
    """16-byte ascii b64 -> b64 -> hex text -> static xor => key bytes"""
    return static_xor(hexb(base64.b64decode(hexb(a16)).decode('latin1')))


def decrypt(dhex, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(hexb(dhex)))


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发千磨万击还坚韧任尔东西南北风َ.smali'
s = open(p, encoding='utf-8').read()
# per-method arrays: method bodies each with local labels (they reset). Use full-file parse but
# restrict to ranges between method starts of interest.
methods = {}
for m in re.finditer(r'\.method (?:public|private|protected|static)?\s*(?:static\s*)?(\w+)\(([^)]*)\)', s):
    methods[m.start()] = m.group(1)

# find 但愿长醉不复醒 body start/end & decode each method separately via its own text span
# method bodies end at next .method or end; use that span for parse_arrays
spans = sorted(methods.keys())
names = {v: k for k, v in methods.items()}


def method_span(pos):
    ends = [x for x in spans if x > pos]
    end = ends[0] if ends else len(s)
    return s[pos:end]


# Process key methods and decode every (key,data) pair they contain
for target in ['但愿长醉不复醒', '斗酒十千恣欢谑', '陈王昔时宴平乐', '古来圣贤皆寂寞', '钟鼓馔玉不足贵']:
    if target not in names:
        continue
    body = method_span(names[target])
    a = parse_arrays(body)
    fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', body)
    print('#### %s #### (arrays: %s)' % (target, {k: len(v) for k, v in a.items()}))
    # The decrypted strings built here are used as args; pair key(32hex)+data in order
    i = 0
    while i + 1 < len(fills):
        k, d = fills[i], fills[i + 1]
        if len(a.get(k, '')) == 32:
            try:
                v = decrypt(a[d], key_from_hexarray(a[k]))
                print('  [%s+%s] %r' % (k, d, v))
            except Exception as e:
                print('  [%s+%s] err %s' % (k, d, e))
            i += 2
        else:
            i += 1
