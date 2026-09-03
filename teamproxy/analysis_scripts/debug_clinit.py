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


def decode_pair(hexkey, hexdata):
    """key flow: bytes(base64 ascii text) -> b64 decode -> hex-string -> hex decode -> static XOR => key bytes
       then data XOR key"""
    kb = hexb(hexkey)
    hexstr = base64.b64decode(kb).decode('latin1')  # e.g. '7E2878427D7C'
    key = static_xor(hexb(hexstr))
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(hexb(hexdata)))


p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发千磨万击还坚韧任尔东西南北风َ.smali'
s = open(p, encoding='utf-8').read()
cl = re.search(r'\.method static constructor <clinit>.*?\.end method', s, re.S)
body = cl.group(0)
arrays = parse_arrays(body)

# walk: each field init: fill key array (32 hex) then decrypt, then data fill; find sput
# simpler: pair arrays by order: 0&1, 2&3, 4&5, 6&7, 8&9, a&b? Wait field order might be interleaved.
# let's just pair (even,odd) per structure of key(16b)+data(N) repeated:
order = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', '10', '11']
pairs = [(order[i], order[i+1]) for i in range(0, len(order), 2)]
for k, d in pairs:
    try:
        print(k, d, '->', decode_pair(arrays[k], arrays[d]))
    except Exception as e:
        print(k, d, 'ERR', e)
