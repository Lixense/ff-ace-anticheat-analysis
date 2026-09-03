import io, sys, re, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# Find all segments that look like base64 (16 chars typical, or longer)
# Pattern in blob: base64text then 4-9 bytes of XOR-garbage then base64text...
# First, extract the big blob around 0x1c3b9
blob_start = 0x1c380
blob = data[blob_start:blob_start + 2000]

# Split on likely XOR-noise: non-base64-alphabet runs
b64chars = set(b'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=')
segments = []
cur = b''
noise = []
for byte in blob:
    if byte in b64chars:
        if noise:
            segments.append(('NOISE', bytes(noise)))
            noise = []
        cur += bytes([byte])
    else:
        if cur:
            segments.append(('B64', cur))
            cur = b''
        noise.append(byte)
if cur:
    segments.append(('B64', cur))
if noise:
    segments.append(('NOISE', bytes(noise)))

out = []
for kind, val in segments:
    if kind == 'B64' and len(val) >= 8:
        try:
            dec = base64.b64decode(val + b'=' * (-len(val) % 4))
            out.append((kind, val, dec))
        except Exception as e:
            out.append((kind, val, b'<err %s>' % str(e).encode()))
    else:
        out.append((kind, val, b''))

for kind, val, dec in out:
    if kind == 'B64':
        # try as utf8/hex
        try:
            as_txt = dec.decode('utf-8')
            print('B64 %r -> %r (hex=%s)' % (val, dec, dec.hex()))
        except Exception:
            print('B64 %r -> raw %s' % (val, dec.hex()))
    else:
        print('NOISE %r' % val)
