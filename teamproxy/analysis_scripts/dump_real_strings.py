import io, sys, struct

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# The real strings are at vaddr 0x1df34..0x1e7cd (file offset == vaddr)
# Dump each target from the RELA list, 100 bytes each, show raw bytes + printable
targets = [0x1df64, 0x1df34, 0x1df8c, 0x1dfc6, 0x1dff2, 0x1e021, 0x1e05e, 0x1e091, 0x1e0bd, 0x1e0f5,
           0x1e12d, 0x1e165, 0x1e197, 0x1e1cb, 0x1e20a, 0x1e244, 0x1e281, 0x1e2bf, 0x1e2f9, 0x1e32d,
           0x1e35c, 0x1e390, 0x1e3c2, 0x1e3ee, 0x1e429, 0x1e458, 0x1e487, 0x1e4b3, 0x1e4df, 0x1e512,
           0x1e541, 0x1e573, 0x1e59f, 0x1e5da, 0x1e60e, 0x1e646, 0x1e675, 0x1e6ac, 0x1e6db, 0x1e70f,
           0x1e740, 0x1e770, 0x1e79b, 0x1e7cd]
for t in sorted(set(targets)):
    chunk = data[t:t+96]
    # printable ascii portion
    asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in chunk)
    print('0x%x: %s' % (t, asc))
