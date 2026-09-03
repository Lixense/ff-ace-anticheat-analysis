import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)


def dec(hx):
    b = bytes(int(hx[i:i+2], 16) for i in range(0, len(hx), 2))
    return bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(b)).decode('utf-8', errors='replace')


print(dec('4e3055794f4463344e44493352446444'))
print(dec('5c0f505b41171c1414'))
print(dec('4e7a6733525464474e4459335154637a'))
print(dec('445a'))
print(dec('4d6b'))
