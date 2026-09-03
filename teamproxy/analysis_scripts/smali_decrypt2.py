import re, io, sys, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)


def parse_smali_arrays(smali_text):
    """Parse .array-data 1 blocks with 0xNNt or 0xNt hex byte literals -> dict label -> hex string."""
    out = {}
    for m in re.finditer(r':array_(\w+)\s*\n(.*?)\n\s*\.end array-data', smali_text, re.S):
        lab = m.group(1)
        body = m.group(2)
        vals = re.findall(r'0x([0-9a-fA-F]{1,2})t', body)
        if vals:
            out[lab] = ''.join(v.zfill(2) for v in vals)
    return out


def static_xor(hexstr):
    b = bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2))
    return bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(b))


def b64decode_bytes(hexstr):
    """Array of ascii base64 chars -> base64 decode -> bytes"""
    b = bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2))
    return base64.b64decode(b)


def key_from_array(hexstr):
    """base64 -> hex-text -> static-xor => key bytes"""
    mid = b64decode_bytes(hexstr).decode('utf-8', errors='replace')
    return static_xor(mid)


def decrypt(hexstr, key):
    b = bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2))
    kb = key
    return bytes(c ^ kb[i % len(kb)] for i, c in enumerate(b))


if __name__ == '__main__':
    p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\com\Sx2\Team\Ban\君不见高堂明镜悲白发长风万里送秋雁对此可以酣高楼َ.smali'
    s = open(p, encoding='utf-8').read()
    arrays = parse_smali_arrays(s)
    for lab in sorted(arrays, key=lambda x: int(x) if x.isdigit() else 0):
        pass
    # method 惟有饮者留其名 is the last method; its arrays: labels listed in body after it
    # take the LAST 10 labels in file order (they appear after the method)
    order = list(arrays.keys())
    print('labels found (file order):', order)
