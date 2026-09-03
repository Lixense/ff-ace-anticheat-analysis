import io, sys, os, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
BASE = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled'
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)


def arr_bytes_hex(hx):
    return bytes(int(hx[i:i+2], 16) for i in range(0, len(hx), 2))


def static_xor(b):
    return bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(b))


def base64_str(b):
    return base64.b64decode(b).decode('utf-8', errors='replace')


def str_xor(b, k):
    kb = k.encode('utf-8')
    return bytes(c ^ kb[i % len(kb)] for i, c in enumerate(b))


def parse_arrays(smali):
    """Return dict label -> bytes hex-string from fill-array-data blocks of type 1 (byte arrays)."""
    out = {}
    # match .array-data 1 blocks: label then hex pairs 0xNNt
    for m in re.finditer(r':array_(\w+)\s*\n(.*?)\.end array-data', smali, re.S):
        label = m.group(1)
        body = m.group(2)
        if '0x' not in body:
            continue
        vals = re.findall(r'0x([0-9a-fA-F]+)t?', body)
        if vals:
            out[label] = ''.join('%02x' % int(v, 16) for v in vals)
    return out


def emulate_method(smali, arrays, method_body):
    """Manually track: need to resolve actual flows. We'll handle the common
    pattern seen in the activity: sequence of stages producing strings appended
    to a StringBuilder, then Shizuku exec array."""
    return None


def dump_file_strings(path):
    s = open(path, encoding='utf-8').read()
    arrays = parse_arrays(s)
    print('== %s : %d arrays' % (os.path.basename(path), len(arrays)))
    return arrays


if __name__ == '__main__':
    p = os.path.join(BASE, 'smali_classes3', 'com', 'Sx2', 'Team', 'Ban',
                     '君不见高堂明镜悲白发长风万里送秋雁对此可以酣高楼َ.smali')
    arrays = dump_file_strings(p)
    for k, v in arrays.items():
        print('array_%s = %s' % (k, v))
