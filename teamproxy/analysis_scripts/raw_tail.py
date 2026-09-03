import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()
# raw dump of 0x1d730 - 0x1da00 (after the last key at 0x1d71c + 16 = 0x1d72c)
chunk = data[0x1d720:0x1db00]
for i in range(0, len(chunk), 16):
    b = chunk[i:i+16]
    asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in b)
    print('0x%04x: %-48s %s' % (0x1d720+i, b.hex(' '), asc))
