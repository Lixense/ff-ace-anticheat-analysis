import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()

def hexdump(off, ln=256):
    for i in range(off, min(off+ln, len(data)), 16):
        b = data[i:i+16]
        asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in b)
        print('0x%04x: %-48s %s' % (i, b.hex(' '), asc))

print('=== crypto section 0x4e20-0x4f80 ===')
hexdump(0x4e20, 0x170)
