import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()

print('file size', len(data))
# Verify length-prefix hypothesis: scan for [len][ascii...] runs
def is_ascii(b):
    return all(32 <= c < 127 for c in b)

# Find every offset where a plausible record starts: byte L (3..250) followed by L printable chars
records = []
i = 7  # skip first 7 header bytes (cb a2 b4 0d b2 19 a3)
n = len(data)
while i < n:
    L = data[i]
    if 3 <= L <= 200 and i + 1 + L <= n and is_ascii(data[i+1:i+1+L]):
        s = data[i+1:i+1+L].decode('latin1')
        records.append((i, L, s))
        i += 1 + L
    else:
        # try 7-bit/2-byte length
        if L & 0x80:
            L2 = data[i+1]
            L = (L & 0x7f) | (L2 << 7)
            if 3 <= L <= 2000 and i + 2 + L <= n and is_ascii(data[i+2:i+2+L]):
                s = data[i+2:i+2+L].decode('latin1')
                records.append((i, L, s))
                i += 2 + L
                continue
        i += 1

print('records found:', len(records))
# Print records with offsets, especially around crypto/download
for off, L, s in records:
    tag = ''
    if any(k in s.lower() for k in ['crypt','cipher','secret','iv','spec','url','http','.so','byte','load','string','getbytes','instance','channels','stream','file','key']):
        tag = ' <<<'
    print('0x%04x L=%3d %r%s' % (off, L, s, tag))
