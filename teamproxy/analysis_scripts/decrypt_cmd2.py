import re, io, sys, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)


def parse_smali_arrays(smali_text):
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
    b = bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2))
    return base64.b64decode(b)


def key_from_array(hexstr):
    mid = b64decode_bytes(hexstr).decode('utf-8', errors='replace')
    return static_xor(mid)


def decrypt(hexstr, key):
    b = bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2))
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(b))


def txt(b):
    return b.decode('utf-8', errors='replace')


if __name__ == '__main__':
    p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\com\Sx2\Team\Ban\君不见高堂明镜悲白发长风万里送秋雁对此可以酣高楼َ.smali'
    s = open(p, encoding='utf-8').read()
    arrays = parse_smali_arrays(s)

    # ---- method 惟有饮者留其名 (Shizuku) uses LAST set (labels reused after each method) ----
    # In file order, each method's arrays appear grouped. The Shizuku method is last, so the final
    # 10 labels in order = its arrays 0..9
    labs = [str(i) for i in range(10)]
    A = {l: arrays[l] for l in labs}
    for l in labs:
        print('array_%s %s (%d bytes)' % (l, A[l], len(A[l]) // 2))

    # arg0 (v1 after second decrypt at lines 725-751): key=array_2, data=array_3
    k = key_from_array(A['2'])
    print('K(2,3) =', repr(k), txt(k))
    arg0 = decrypt(A['3'], k)
    print('arg0 =', repr(arg0), txt(arg0))

    # arg1 (v2 at 753-777): key=array_4 data=array_5
    k2 = key_from_array(A['4'])
    print('K(4,5) =', repr(k2), txt(k2))
    arg1 = decrypt(A['5'], k2)
    print('arg1 =', repr(arg1), txt(arg1))

    # sb pieces
    # init sb (v1 at 697-723): key=array_0, data=array_1
    k0 = key_from_array(A['0'])
    sb0 = decrypt(A['1'], k0)
    print('SB0 =', repr(sb0), txt(sb0))

    # append2 (v3 at 783-809): key=array_6 data=array_7
    k6 = key_from_array(A['6'])
    sb2 = decrypt(A['7'], k6)
    print('SB2 =', repr(sb2), txt(sb2))

    # append3 (v2 at 845-857): key=array_8 data=array_9
    k8 = key_from_array(A['8'])
    sb3 = decrypt(A['9'], k8)
    print('SB3 =', repr(sb3), txt(sb3))
