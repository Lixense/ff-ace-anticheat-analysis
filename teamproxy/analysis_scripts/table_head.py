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
        if key and 3 <= len(noise) <= 24:
            entries.append((i, key, noise))
        i = j
    else:
        i += 1

# Hypothesis: each entry is: 16b64(6-byte KEY, but only SOME bytes matter) + noise where
# noise = XOR-encoded chars. The 'ad d1 c0' const = key[0..2]^noise[0..2] means noise[0..2]
# are NOT random; they might be the FIRST 3 CHARS of the plaintext string!
# i.e. plaintext[i] = noise[i] ^ key[i]. If plaintext started 'htt' for a URL we'd get:
print('Test: noise[0:3] ^ key[0:3] as chars:')
for off, key, noise in entries:
    print('off=%06x  %r' % (off, bytes(n ^ key[k] for k, n in enumerate(noise[:3]))))
