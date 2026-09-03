import io, sys, os, re, base64

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
                out.append((k, d, decrypt(a[d], hexkey_from(a[k]))))
            except Exception:
                out.append((k, d, b'<err>'))
            i += 2
        else:
            i += 1
    return out


# 1) Launcher activity = exported MAIN: 谁家今夜扁舟子 is not exported? Check manifest mapping
# manifest: launcher = 君不见...谁家今夜扁舟子何处相思明月楼 (exported). So launcher is THIS one (谁家) which shows Splash/Verify screen?
# Actually that is the API/verify activity. 2nd activity = 君不见...长风万里送秋雁对此可以酣高楼 (the copy one).
# 3rd (千磨万击) = injector.
# Check 长风万里 activity onCreate flow: what it does (copy from .hiddenprjkt?)
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\com\Sx2\Team\Ban\君不见高堂明镜悲白发长风万里送秋雁对此可以酣高楼َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)
print('######## 长风万里 (copy activity) ########')
for part in parts:
    mm = re.search(r'\.method\s+(?:public|private|protected|static)?\s*(?:static\s*)?([\w<>]+)\(', part)
    if not mm:
        continue
    nm = mm.group(1)
    if nm in ('onCreate', 'onResume', 'onClick', '古来圣贤皆寂寞', '但愿长醉不复醒', '惟有饮者留其名', '君不见高堂明镜悲白发'):
        print('==== %s ====' % nm)
        lines = []
        for ln in part.split('\n'):
            if ln.strip().startswith(':array_'):
                break
            lines.append(ln)
        # limit output
        print('\n'.join(lines[:120]))
