import io, sys, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)

data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()
b64set = set(b'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/')

# collect all 16-char b64 tokens in the table region
toks = []
i = 0x1bf00
while i < 0x1e800:
    if all(data[i+j] in b64set for j in range(16)):
        tok = data[i:i+16]
        toks.append((i, tok))
        i += 16
        while i < 0x1e800 and data[i] in b64set:
            i += 1
    else:
        i += 1

print('tokens:', len(toks))
for off, tok in toks[:40]:
    try:
        hexstr = base64.b64decode(tok + b'==').decode('latin1')
        # XOR the hex TEXT (ascii chars) with Arabic key, like Java's 君不见高堂明镜悲白发(String)
        out = bytes(ord(hexstr[k]) ^ KEYB[k % len(KEYB)] for k in range(len(hexstr)))
        print('off=%06x hexstr=%s -> xor_arabic=%s' % (off, hexstr, out))
    except Exception as e:
        print('off=%06x err %s' % (off, e))
