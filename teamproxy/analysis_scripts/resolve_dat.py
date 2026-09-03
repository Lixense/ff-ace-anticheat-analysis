import io, sys, struct

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# DAT_0011c15e -> vaddr 0x11c15e. file offset == vaddr for this ELF.
addrs = [0x11c15e, 0x11c16e, 0x117ed6, 0x11ad01, 0x11a6bb, 0x11ac0e, 0x11ac2d, 0x119b87,
         0x11a18a, 0x11567b, 0x116867, 0x119a18, 0x11a1c0]
for a in addrs:
    chunk = data[a:a+128]
    # show hex + printable
    asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in chunk)
    print('0x%x: %s' % (a, asc[:80]))
    print('      hex: %s' % chunk[:48].hex())
