import io, sys, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()
b64set = set(b'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/')

# Re-scan just the table region 0x1bf00-0x1e000 with exact per-entry alignment.
# Observation from the raw dump: entries look like:
#   <16 b64><noise 3..16>
# where b64 -> 12 hex chars. Let's list them with their hex decode and the noise in hex,
# then try: plaintext = noise[i] ^ keyByte where keyByte cycles over the 6 key bytes
# in the *reverse* direction, or the noise is ciphertext of an ASCII string XORed with key
# but key applied with offset = entry index. Print everything so we can eyeball.
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
        while j < len(data) and data[j] not in b64set and len(noise) < 16:
            noise += bytes([data[j]])
            j += 1
        if key and 3 <= len(noise) <= 16:
            entries.append((i, key, noise))
        i = j
    else:
        i += 1

print('aligned entries in table region:', len(entries))
for off, key, noise in entries[:60]:
    # print key and noise, plus xor with key forward/reverse and key+index offset guesses
    fwd = bytes(n ^ key[k % len(key)] for k, n in enumerate(noise))
    rev = bytes(n ^ key[-(k % len(key)) - 1] for k, n in enumerate(noise))
    print('off=%06x key=%s noise=%s fwd=%s rev=%s' % (off, key.hex(), noise.hex(), fwd.hex(), rev.hex()))
