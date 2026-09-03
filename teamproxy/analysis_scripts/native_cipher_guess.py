import io, sys, re, base64, struct

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# scan whole file for the pattern: 16 base64 chars followed by ~5-12 bytes of non-b64 'noise'
# We'll parse strictly: after a 16-char b64 token, capture the following run of non-b64 bytes (3..14)
b64set = set(b'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/')
results = []
i = 0
while i < len(data) - 32:
    # 16 b64 chars
    if all(data[i+j] in b64set for j in range(16)):
        tok = data[i:i+16]
        # must be followed by non-b64
        j = i + 16
        noise = b''
        while j < len(data) and data[j] not in b64set and len(noise) < 20:
            noise += bytes([data[j]])
            j += 1
        if 3 <= len(noise) <= 14:
            results.append((i, tok, noise))
            i = j
            continue
    i += 1

print('found', len(results), 'candidate entries')
out_lines = []
for off, tok, noise in results:
    try:
        dec = base64.b64decode(tok + b'==')
        hexstr = dec.decode('latin1')  # 12 hex chars
        keybytes = bytes.fromhex(hexstr) if len(hexstr) == 12 else b''
        # try XOR key with noise
        if keybytes:
            xored = bytes(n ^ keybytes[k % len(keybytes)] for k, n in enumerate(noise))
            # also try reversed
            xored2 = bytes(n ^ keybytes[-(k % len(keybytes)) - 1] if False else n for k, n in enumerate(noise))
            out_lines.append('off=0x%x key_hex=%s key=%s noise=%s xor=%s' % (off, hexstr, keybytes.hex(), noise.hex(), xored))
    except Exception as e:
        out_lines.append('off=0x%x tok=%s err %s' % (off, tok.decode('latin1'), e))
print('\n'.join(out_lines[:120]))
