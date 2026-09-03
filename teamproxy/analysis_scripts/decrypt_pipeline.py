import io, sys, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)


def arr_from_hex(hx):
    return bytes(int(hx[i:i+2], 16) for i in range(0, len(hx), 2))


def stage1_b64(arr_ascii_hex):
    """bytes are ASCII of base64 text; base64-decode -> string"""
    b = arr_from_hex(arr_ascii_hex)
    return base64.b64decode(b).decode('utf-8', errors='replace')


def static_decrypt(hexstr):
    """君不见高堂明镜悲白发(): hex decode then XOR with static key -> bytes/string"""
    b = bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2))
    out = bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(b))
    return out


def xor_with_key(cipher_hex, key_str):
    b = arr_from_hex(cipher_hex)
    kb = key_str.encode('utf-8')
    out = bytes(c ^ kb[i % len(kb)] for i, c in enumerate(b))
    return out


if __name__ == '__main__':
    # test from method 惟有饮者留其名
    array_0 = '4e3055794f4463344e44493352446444'  # key1 cipher -> base64 text -> hex -> static xor -> KEY1
    array_1 = '5c0f505b41171c1414'                # actual ciphertext part 1
    array_2 = '4e7a6733525464474e4459335154637a'  # key2
    array_3 = '445a'                              # ciphertext part 2
    array_4 = '4d6b'                              # key3? -> wait array_4 is 2 bytes '4d6b'
    array_5 = '445a' if False else None

    # Stage: for arrays of len 16 -> they are base64 of hex string (the key material)
    a0 = stage1_b64(array_0)
    print('stage1 a0 =', repr(a0))
    k1 = static_decrypt(a0)
    print('KEY1 raw =', repr(k1))
    print('KEY1 str =', repr(k1.decode('utf-8', errors='replace')))

    # decrypt part1
    p1 = xor_with_key(array_1, k1.decode('utf-8', errors='replace'))
    print('PART1 =', repr(p1.decode('utf-8', errors='replace')))
