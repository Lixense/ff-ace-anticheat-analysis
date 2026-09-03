import io, sys, os, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)


def static_hex_xor(hexstr):
    b = bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2))
    return bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(b))


def decode_key_hex(hexstr):
    """array like 4e3055794f4463344e44493352446444 = ascii base64 -> b64decode -> ascii hex string -> static XOR -> raw key"""
    b = bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2))
    s = base64.b64decode(b).decode('utf-8', errors='replace')  # hex string
    return static_hex_xor(s)


def decrypt_with_key(cipher_hex, key):
    b = bytes(int(cipher_hex[i:i+2], 16) for i in range(0, len(cipher_hex), 2))
    kb = key
    return bytes(c ^ kb[i % len(kb)] for i, c in enumerate(b))


def str_join_plain(hexstr):
    """raw bytes -> ascii"""
    return bytes(int(hexstr[i:i+2], 16) for i in range(0, len(hexstr), 2)).decode('utf-8', errors='replace')


if __name__ == '__main__':
    # arrays from method 惟有饮者留其名 (second group in file)
    arrays = {
        'a0': '4e3055794f4463344e44493352446444',
        'a1': '5c505b41171c1414',
        'a2': '4e7a6733525464474e4459335154637a',
        'a3': '445a',
        'a4': '4d6b5179526a64434e444533517a6335',
        'a5': '4f',
        'a6': '4e7a6b79525463344e44453352446443',
        'a7': '425741131d44141e404459105556561f53415d5244531b1c1e5e5055565e46105e5a471f',
        'a8': '4e305133525464424d54493352446335',
        'a9': '1d1c16',
    }
    k1 = decode_key_hex(arrays['a0'])
    print('K1', repr(k1))
    s1 = decrypt_with_key(arrays['a1'], k1)
    print('S1', repr(s1))

    k2 = decode_key_hex(arrays['a2'])
    print('K2', repr(k2))
    s2 = decrypt_with_key(arrays['a3'], k2)
    print('S2', repr(s2))

    k3 = decode_key_hex(arrays['a4'])
    print('K3', repr(k3))
    s3 = decrypt_with_key(arrays['a5'], k3)
    print('S3', repr(s3))

    k4 = decode_key_hex(arrays['a6'])
    print('K4', repr(k4))
    s4 = decrypt_with_key(arrays['a7'], k4)
    print('S4', repr(s4))

    k5 = decode_key_hex(arrays['a8'])
    print('K5', repr(k5))
    s5 = decrypt_with_key(arrays['a9'], k5)
    print('S5', repr(s5))
