import io, sys, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()
b64set = set(b'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/')
i = 0x1bf00
entries = []
while i < 0x1e800:
    if all(data[i+j] in b64set for j in range(16)):
        tok = data[i:i+16]
        try:
            dec = base64.b64decode(tok + b'==').decode('latin1')
            key = bytes.fromhex(dec) if len(dec) == 12 and all(c in '0123456789abcdefABCDEF' for c in dec) else None
        except Exception:
            key = None
        j = i + 16
        noise = b''
        while j < len(data) and data[j] not in b64set and len(noise) < 24:
            noise += bytes([data[j]])
            j += 1
        if key and 4 <= len(noise) <= 24:
            entries.append((i, key, noise))
        i = j
    else:
        i += 1

print('entries:', len(entries))
# Try: skip first 3 noise bytes, XOR rest with key rolling
for off, key, noise in entries[:50]:
    body = noise[3:]
    if not body:
        continue
    x = bytes(n ^ key[k % len(key)] for k, n in enumerate(body))
    printable = all(32 <= c < 127 for c in x)
    print('off=%06x key=%s noise=%s body_xor=%s %s' % (off, key.hex(), noise.hex(), x, '<PRINT>' if printable else ''))
