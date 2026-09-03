import io, sys, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

def key_from_b64arr(arr16):
    hexstr = base64.b64decode(arr16).decode('latin1')
    raw = bytes.fromhex(hexstr)
    return bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(raw))

def dec(ct, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(ct))

b64set = set(b'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=')
keypos = []
for off in range(0x1be00, 0x1f000):  # extend scan range
    if all(data[off+j] in b64set for j in range(16)):
        try:
            hx = base64.b64decode(data[off:off+16]).decode('latin1')
            if len(hx) == 12 and all(c in '0123456789abcdefABCDEF' for c in hx):
                keypos.append(off)
        except Exception:
            pass
print('keys:', len(keypos), hex(keypos[0]), hex(keypos[-1]))
# decode the tail region 0x1d700+ with correct sequential pairing but allow ciphertext
# to end when next key starts. Print region around 0x1d700-0x1e000 decoded with each key
for i, kp in enumerate(keypos):
    if kp < 0x1d700:
        continue
    key = key_from_b64arr(data[kp:kp+16])
    end = keypos[i+1] if i+1 < len(keypos) else min(kp + 400, len(data))
    L = end - kp - 16
    if L <= 0:
        continue
    ct = data[kp+16:kp+16+L]
    pt = dec(ct, key)
    asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in pt)
    print('0x%x L=%d: %r' % (kp, L, pt[:200]))
