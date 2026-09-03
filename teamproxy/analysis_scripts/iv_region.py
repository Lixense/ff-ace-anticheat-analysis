import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()

def hexdump(off, ln=64):
    for i in range(off, min(off+ln, len(data)), 16):
        b = data[i:i+16]
        asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in b)
        print('0x%04x: %-48s %s' % (i, b.hex(' '), asc))

print('=== around x4Rq (0x4da0) ===')
hexdump(0x4d80, 0x60)
print()
print('=== around IV/spe truncation (0x4e80) ===')
hexdump(0x4e80, 0x50)
print()
# bytes right after 'x4Rq' and after 'AES/CTR/NoPadding'
# find byte offsets of key strings
for s in [b'x4Rq', b'javax.crypto.spe', b'IvParameterSpec', b'AES/CTR/NoPadding']:
    i = data.find(s)
    print('%r @ 0x%x, next 8 bytes: %s' % (s, i, data[i+len(s):i+len(s)+8].hex(' ')))
