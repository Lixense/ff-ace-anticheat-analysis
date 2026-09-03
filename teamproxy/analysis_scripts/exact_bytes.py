import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# The onCreate filled: 0x10 bytes from &DAT_0011c15e, 5 bytes from &DAT_0011c16e
# Those DAT addresses in Ghidra = file offset 0x11c15e? No: Ghidra base 0x100000, so file = 0x1c15e
for name, addr, n in [('c15e_16B', 0x1c15e, 16), ('c16e_5B', 0x1c16e, 5),
                      ('ad01?', 0x1ad01, 16), ('a6bb?', 0x1a6bb, 16), ('ac0e?', 0x1ac0e, 16)]:
    chunk = data[addr:addr+n]
    asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in chunk)
    print('%s @0x%x: %s  hex=%s' % (name, addr, asc, chunk.hex()))
