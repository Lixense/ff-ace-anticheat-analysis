import io, sys, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

def xor_with_key_bytes(ct, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(ct))

def xor_with_key_str(ct, keystr):
    kb = keystr.encode('latin1')
    return bytes(c ^ kb[i % len(kb)] for i, c in enumerate(ct))

# c193 = 16B ascii b64 'N0Y3NTc4MTIyQjdB'
b64_193 = data[0x1c193:0x1c193+16].decode()
hexstr_193 = base64.b64decode(b64_193).decode('latin1')  # 7F7578122B7A
print('b64:', b64_193, 'hexstr:', hexstr_193)

# candidate keys:
# 1) raw hexstr ascii as key string
# 2) arabic-xor of hexstr bytes -> as str
arabic_xor = bytes(ord(hexstr_193[i]) ^ KEYB[i % len(KEYB)] for i in range(len(hexstr_193)))
print('arabic xor:', arabic_xor)

# cipher c1a3 (0x1b = 27 bytes)
ct = data[0x1c1a3:0x1c1a3+27]
print('ct:', ct)

for name, k in [('hexstr', hexstr_193.encode()), ('arabic', arabic_xor)]:
    pt = xor_with_key_bytes(ct, k)
    print('%s -> %r' % (name, pt))
    # also try with key interpreted as hex-decoded
    try:
        kh = bytes.fromhex(hexstr_193)
        pt2 = xor_with_key_bytes(ct, kh)
        print('  hexbytes -> %r' % pt2)
    except Exception:
        pass
