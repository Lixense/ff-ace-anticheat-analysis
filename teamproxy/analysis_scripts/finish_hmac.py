import io, sys, os, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)

USERKEY = 'SX2-TEAM-HAW8E0RP'


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
    if not key:
        return b''
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(hexb(hexdata)))


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)

# Second-stage: the double-decrypt result is base64 ascii; base64-decode it and then maybe it's hex -> XOR userkey?
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if m and m.group(1) in ('请君为我倾耳听', '钟鼓馔玉不足贵'):
        a = parse_arrays(part)
        fills = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', part)
        pairs = []
        i = 0
        while i + 1 < len(fills):
            k, d = fills[i], fills[i + 1]
            if len(a.get(k, '')) == 32:
                pairs.append((k, d))
                i += 2
            else:
                i += 1
        print('==== %s ====' % m.group(1))
        for k, d in pairs:
            data_hex = a[d]
            try:
                k1 = key_from(a[k])
            except Exception:
                continue
            # stage1: xor with key
            st1 = decrypt(data_hex, k1)
            # It looks like base64 text: try decode
            try:
                st2 = base64.b64decode(st1)
                print('pair %s/%s: st1=%r' % (k, d, st1))
                print('    b64dec -> %r' % st2)
                # st2 could be hex string of real secret or direct; print ascii and hex
                try:
                    print('    as utf8: %r' % st2.decode('utf-8'))
                except Exception:
                    print('    raw hex: %s' % st2.hex())
            except Exception as e:
                print('pair %s/%s: st1=%r not b64 (%s)' % (k, d, st1, e))
