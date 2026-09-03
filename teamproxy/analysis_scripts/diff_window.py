import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
xz = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc','rb').read()
qw = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libQWERTYUIOPAS.so.enc','rb').read()

# Both files: same ciphertext prefix 0..0x28 -> same plaintext prefix (their ELF headers match).
# At 0x28 they diverge. In an ELF, 0x28 = e_shoff first byte. XZ has 0x20, QW 0x50 at 0x28.
# e_shoff low bytes 0x20/0x50 -> suggests section header tables at 0x...20/0x...50? not typical.
# The pattern 0x20 vs 0x50 at 0x28 with all following bytes matching until 0x2d-ish then diverging
# Actually XZ[0x28]=20, QW[0x28]=50, then XZ[0x29]=ee vs QW[0x29]=bf, but then XZ[0x2a..0x40] == QW[0x2a..0x40]
# That means plaintexts differ ONLY at 0x28 and 0x29 -> a 2-byte field differs. e_shoff bytes 0-1.
# => e_shoff low 2 bytes differ (0x20ee vs 0x50bf? wait LE: byte0=0x20/0x50, byte1=0xee/0xbf shared? no byte1 differs too: XZ ee vs QW bf)
# print exact differing bytes in 0x28..0x40 window
for i in range(0x28, 0x48):
    a, b = xz[i], qw[i]
    print('0x%02x: xz=%02x qw=%02x %s' % (i, a, b, 'DIFF' if a != b else ''))
