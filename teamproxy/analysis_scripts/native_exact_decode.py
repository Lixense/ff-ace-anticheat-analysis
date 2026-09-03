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

# find all key positions
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

# next non-key start = keypos[i+1]; ciphertext may be keypos[i]+16 .. keypos[i+1]
# But there may be decoy b64 inside ciphertext (like 'NDU='). Instead: decode ct = [kp+16 .. kp+16+L]
# for L from 3 to (next_key - kp - 16) and pick the L that yields a full printable+spaces string.
def printable_score(b):
    if not b: return -1
    letters = sum(1 for c in b if 32 <= c < 127)
    return letters / len(b)

results = []
for i, kp in enumerate(keypos):
    key = key_from_b64arr(data[kp:kp+16])
    end = keypos[i+1] if i+1 < len(keypos) else kp + 200
    maxlen = min(end - kp - 16, 120)
    best = None
    for L in range(3, maxlen+1):
        ct = data[kp+16:kp+16+L]
        pt = dec(ct, key)
        sc = printable_score(pt)
        # require mostly printable with reasonable letters and no control chars
        if all(32 <= c < 127 or c in (9,10,13) for c in pt) and sc > 0.92:
            # penalize strings without spaces if long, but allow single words
            best = (L, pt)
            break
    if best:
        L, pt = best
        results.append((kp, L, key, pt))

for kp, L, key, pt in results:
    print('key@0x%x len=%d key=%s -> %r' % (kp, L, key.hex(), pt))
print('total:', len(results))
