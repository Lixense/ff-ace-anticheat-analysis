import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()

# HybridCLR metadata blobs typically: [method-def table][IL bodies]. The string heap region
# we found (0x4400-0x5060) is one contiguous block of [len][string] records ending at 0x5055
# ('c' then 00s). The method IL bodies live right after the records: 0x5056 onward.
def hexdump(off, ln=384):
    for i in range(off, min(off+ln, len(data)), 16):
        b = data[i:i+16]
        asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in b)
        print('0x%04x: %-48s %s' % (i, b.hex(' '), asc))

print('=== after string records 0x5050-0x50c0 ===')
hexdump(0x5050, 0x70)
print()
print('=== 0x50c0-0x5160 (tail) ===')
hexdump(0x50c0, 0xa0)
