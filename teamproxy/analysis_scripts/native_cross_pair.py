import io, sys, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()
b64set = set(b'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/')
entries = []  # (offset, keybytes_or_None, noise)

i = 0
while i < len(data) - 40:
    if all(data[i+j] in b64set for j in range(16)):
        tok = data[i:i+16]
        # decode to hex text; if all hex and 12 chars -> key
        try:
            dec = base64.b64decode(tok + b'==').decode('latin1')
            keybytes = bytes.fromhex(dec) if len(dec) == 12 and all(c in '0123456789abcdefABCDEF' for c in dec) else None
        except Exception:
            keybytes = None
        j = i + 16
        noise = b''
        while j < len(data) and data[j] not in b64set and len(noise) < 16:
            noise += bytes([data[j]])
            j += 1
        if 3 <= len(noise) <= 16:
            entries.append((i, keybytes, noise))
            i = j
            continue
    i += 1

# Try cross pairing: entry[n].noise XOR entry[n+1].key (key usually 6 bytes)
print('entries:', len(entries))
for n in range(len(entries) - 1):
    off, key, noise = entries[n]
    off2, key2, noise2 = entries[n+1]
    if key2:
        x = bytes(a ^ key2[k % len(key2)] for k, a in enumerate(noise))
        # printable?
        if all(32 <= c < 127 for c in x) and len(x) >= 3:
            print('off 0x%x noise %s ^ nextkey %s = %r' % (off, noise.hex(), key2.hex(), x))
    if key:
        x2 = bytes(a ^ key[k % len(key)] for k, a in enumerate(noise2))
        if all(32 <= c < 127 for c in x2) and len(x2) >= 3:
            print('off 0x%x nextnoise %s ^ key %s = %r' % (off, noise2.hex(), key.hex(), x2))
