import io, sys, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

def arabic_key_from_b64hex16(b64bytes_ascii):
    """16 ascii bytes (b64) -> hex text -> XOR arabic key -> bytes (the per-string key)"""
    hexstr = base64.b64decode(b64bytes_ascii).decode('latin1')
    return bytes(ord(hexstr[i]) ^ KEYB[i % len(KEYB)] for i in range(len(hexstr)))

def xor_with_key(ct, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(ct))

# Arrays referenced in onCreate 0x31198
# name: (file_addr, length, how_used)
# Each "key" is a 16B ascii b64 array; the DATA is a separate array.
# From the code: NewByteArray(n) + SetByteArrayRegion(&DAT_xx) then calls decryptor with a key string
# which was previously built. We must identify the key for each. The onCreate pattern:
#   0x10 array from DAT_0011c15e -> new String -> (key stage)
#   key = arabic(key_from c15e). Then 5B array c16e XOR key.
# In 31198: uses c193(0x10) w/ new String, c1a3(0x1b) w/ ([B,String,I), c177(0x10), c187(8), c18f(4) w/...
# Let's just decode each 16B b64 key and each cipher and try pairing sequentially.
addrs = {
 'c15e_16': 0x1c15e, 'c16e_5': 0x1c16e,
 'c177_16': 0x1c177, 'c187_8': 0x1c187, 'c18f_4': 0x1c18f,
 'c193_16': 0x1c193, 'c1a3_27': 0x1c1a3,
}
raw = {}
for name, a in addrs.items():
    raw[name] = data[a:a+int(name.split('_')[1])]
    print(name, raw[name])

# Decode each: first try the standard: key16 ascii b64 -> arabic -> key; cipher XOR key
def decode_entry(b64arr, ct):
    key = arabic_key_from_b64hex16(b64arr)
    return xor_with_key(ct, key), key

# pair keys (16B b64) with following ciphers
for keyname, ctname in [('c15e_16','c16e_5'), ('c193_16','c1a3_27'), ('c177_16','c187_8')]:
    pt, key = decode_entry(raw[keyname], raw[ctname])
    print('%s+%s key=%s -> %r' % (keyname, ctname, key.hex(), pt))
# c18f_4 is standalone 4 bytes used with StringBuilder append as-is; try arabic directly
ct4 = raw['c18f_4']
print('c18f_4 raw:', ct4)
