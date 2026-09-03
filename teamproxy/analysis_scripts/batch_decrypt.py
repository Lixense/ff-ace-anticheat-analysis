import io, sys, os, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)


def parse_arrays(smali_text):
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


def b64d(hexstr):
    b = bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2))
    return base64.b64decode(b)


def xordata(hexstr, key):
    b = bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2))
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(b))


def decode_pair(hexkey, hexdata):
    k = static_xor(b64d(hexkey).decode('latin1'))
    return xordata(hexdata, k)


def decode_clinit(s):
    results = []
    cl = re.search(r'\.method static constructor <clinit>.*?\.end method', s, re.S)
    if not cl:
        return results
    body = cl.group(0)
    arrays = parse_arrays(body)

    # tokenize body into logical statements by following register flow is complex;
    # instead find pattern: array_K fill ... sput with same reg. Do a light scan:
    # for every array used as key (16 bytes ending with base64ish ascii), look for
    # subsequent fill of another array followed by sput-object ... :Ljava/lang/String;
    lines = body.split('\n')
    key_pending = None
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        m = re.match(r'fill-array-data\s+v\d+,\s*:array_(\w+)', line)
        if m and key_pending is None:
            lab = m.group(1)
            if lab in arrays and len(arrays[lab]) == 32:  # 16 bytes
                key_pending = lab
                i += 1
                continue
        m2 = re.match(r'sput-object\s+v\d+,\s*L[\w/$]+;->([\w]+):Ljava/lang/String;', line)
        if m2 and key_pending:
            fld = m2.group(1)
            # find the data array used between key fill and sput: scan previous ~40 lines
            prev = '\n'.join(lines[max(0, i-60):i])
            dm = re.findall(r'fill-array-data\s+v\d+,\s*:array_(\w+)', prev)
            if dm:
                for dlab in dm[-3:]:
                    if dlab in arrays and arrays[dlab] != arrays[key_pending] and len(arrays[dlab]) > 2:
                        try:
                            results.append((fld, decode_pair(arrays[key_pending], arrays[dlab])))
                        except Exception as e:
                            results.append((fld, ('<err>').encode()))
                        break
            key_pending = None
        i += 1
    return results


if __name__ == '__main__':
    import glob
    for pat in [r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\*.smali',
                r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\com\Sx2\Team\Ban\*.smali']:
        for p in glob.glob(pat):
            s = open(p, encoding='utf-8').read()
            res = decode_clinit(s)
            if res:
                print('##', os.path.basename(p))
                for fld, val in res:
                    try:
                        txt = val.decode('utf-8')
                    except Exception:
                        txt = repr(val)
                    print('   %s = %r' % (fld, txt))
