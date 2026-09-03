import re, sys, base64, os, io

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = KEY.encode('utf-8')


def hex_to_bytes(hx):
    return bytes(int(hx[i:i+2], 16) for i in range(0, len(hx), 2))


def xor_dec(b):
    return bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(b))


def decode_hex_then_xor(s):
    return xor_dec(hex_to_bytes(s)).decode('utf-8', errors='replace')


def decode_b64_then_xor(s):
    try:
        return xor_dec(base64.b64decode(s)).decode('utf-8', errors='replace')
    except Exception as e:
        return '<ERR %s>' % e


if __name__ == '__main__':
    tests = [
        ('4e3055794f4463344e44493352446444', 'arr0'),
        ('5c0f505b41171c1414', 'arr1'),
        ('4e7a6733525464474e4459335154637a', 'arr2'),
        ('445a', 'arr3'),
        ('4d6b', 'arr4'),
    ]
    for hx, name in tests:
        print(name, decode_hex_then_xor(hx))
