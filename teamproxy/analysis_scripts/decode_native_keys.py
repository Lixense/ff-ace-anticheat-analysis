import io, sys, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# Extract all 16-char b64 runs in 0x1b000-0x1e000 region and try Java-style decode:
# b64 -> hex text -> XOR with Arabic key low bytes -> ???
# OR the string IS the key and ciphertext is elsewhere. Print decoded hex-text for review.
b64set = set(b'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/')
seen = set()
for off in range(0x1b000, 0x1e200):
    if data[off] in b64set and all(data[off+j] in b64set for j in range(16)):
        tok = data[off:off+16]
        if tok in seen:
            continue
        seen.add(tok)
        try:
            hexstr = base64.b64decode(tok + b'==').decode('latin1')
        except Exception:
            continue
        if not all(c in '0123456789abcdefABCDEF' for c in hexstr):
            continue
        # Java-style: hexdecode then XOR arabic
        raw = bytes.fromhex(hexstr)
        xj = bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(raw))
        print('0x%x b64=%s hex=%s raw=%s xorA=%s' % (off, tok.decode(), hexstr, raw.hex(), xj))
