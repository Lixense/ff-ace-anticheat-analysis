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
for off in range(0x1be00, 0x1e800):
    if all(data[off+j] in b64set for j in range(16)):
        try:
            hx = base64.b64decode(data[off:off+16]).decode('latin1')
            if len(hx) == 12 and all(c in '0123456789abcdefABCDEF' for c in hx):
                keypos.append(off)
        except Exception:
            pass

# The layout: key(16) + ciphertext(chars). Next key begins right after ciphertext.
# So ciphertext length = next_key_pos - (kp+16). Print the full decode for each.
results = []
for i, kp in enumerate(keypos):
    key = key_from_b64arr(data[kp:kp+16])
    end = keypos[i+1] if i+1 < len(keypos) else kp + 120
    L = end - kp - 16
    if L < 1: continue
    ct = data[kp+16:kp+16+L]
    pt = dec(ct, key)
    results.append((kp, L, key, pt))

for kp, L, key, pt in results:
    asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in pt)
    print('key@0x%x len=%d -> %r  [%s]' % (kp, L, pt, asc))
