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

# Known-good key arrays (16B ascii b64) live around 0x1c000-0x1e000, ciphertext follows after each key.
# Format seen: <16B b64 key> then <ciphertext bytes> until next printable string region.
# Strategy: for each 16B b64 key position in 0x1be00..0x1e800, decode; then scan the NEXT ~60 bytes
# as candidate ciphertext; if decryption yields printable ASCII, report key->ct->pt.
b64set = set(b'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=')
keypos = []
for off in range(0x1be00, 0x1e800):
    if all(data[off+j] in b64set for j in range(16)):
        # confirm b64 decodes to 12 hex chars
        try:
            hx = base64.b64decode(data[off:off+16]).decode('latin1')
            if len(hx) == 12 and all(c in '0123456789abcdefABCDEF' for c in hx):
                keypos.append(off)
        except Exception:
            pass

print('key positions:', len(keypos))
results = []
# After a key, the ciphertext usually starts at keypos+16 (a few noise bytes may intervene)
for kp in keypos:
    key = key_from_b64arr(data[kp:kp+16])
    # candidate start offsets: kp+16 .. kp+24
    for start in range(kp+16, min(kp+25, len(data)-4)):
        # candidate lengths 3..64
        for ln in range(3, 65):
            if start+ln > len(data): break
            ct = data[start:start+ln]
            pt = dec(ct, key)
            if all(32 <= c < 127 for c in pt) and pt.count(b' ') < 3:
                results.append((kp, start, ln, key, pt))
                break  # first good length for this start
        # only try the first plausible start that gives all-ascii
# dedupe and print
seen = set()
for kp, start, ln, key, pt in results:
    if pt in seen: continue
    seen.add(pt)
    print('key@0x%x ct@0x%x len=%d key=%s -> %r' % (kp, start, ln, key.hex(), pt))
