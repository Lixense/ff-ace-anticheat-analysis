import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()

def hexdump(off, ln=384):
    for i in range(off, min(off+ln, len(data)), 16):
        b = data[i:i+16]
        asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in b)
        print('0x%04x: %-48s %s' % (i, b.hex(' '), asc))

# The string heap records are stored as [len][bytes] with len = byte count for <128.
# IV string may be stored between 'getBytes' (0x4e63) and 'SecretKeySpec' (0x4e6b)
print('=== 0x4e5c - 0x4f00 ===')
hexdump(0x4e5c, 0xA4)
print()
# Check around the tail where System.load + cache_prefs.delete + the __aa etc strings:
print('=== 0x4f60 - 0x5060 ===')
hexdump(0x4f60, 0x100)
