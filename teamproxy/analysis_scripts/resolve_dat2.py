import io, sys, struct

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# Ghidra image base = 0x100000 (its load address). real file offset = ghidra_addr - 0x100000
addrs = [0x11c15e, 0x11c16e, 0x117ed6, 0x11ad01, 0x11a6bb, 0x11ac0e, 0x11ac2d, 0x119b87,
         0x11a18a, 0x11567b, 0x116867, 0x119a18, 0x11a1c0, 0x11c000, 0x11d000]
for a in addrs:
    off = a - 0x100000
    if off < 0 or off >= len(data):
        print('0x%x: out of range (off 0x%x)' % (a, off))
        continue
    chunk = data[off:off+96]
    asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in chunk)
    print('0x%x (off 0x%x): %s' % (a, off, asc[:90]))
