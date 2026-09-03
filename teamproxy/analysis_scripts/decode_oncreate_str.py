import io, sys, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)

# key material: 16-byte ascii = base64 of hex text
b64text = 'Mjk3QTI4NDMyQjdF'
hexstr = base64.b64decode(b64text).decode('latin1')   # '297A28432B7E'
print('hexstr:', hexstr)
key = bytes(ord(hexstr[i]) ^ KEYB[i % len(KEYB)] for i in range(len(hexstr)))
print('key:', key)

# decrypt the 5-byte ciphertext with the key
ct = bytes.fromhex('0344165c17')
pt = bytes(c ^ key[i % len(key)] for i, c in enumerate(ct))
print('plaintext:', pt)
