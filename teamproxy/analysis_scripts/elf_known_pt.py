import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
xz = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc','rb').read()

# plaintext guess for first 0x28: standard arm64 ELF header (libs built by same toolchain,
# ET_DYN, entry at 0x... but e_entry bytes at 0x18-0x1f may differ between libs!
# Since XZ and QW match for 0x28, e_entry(0x18-0x1f) matches too => both libs have same e_entry,
# OR bytes 0x18-0x1f are not e_entry.
# Recover keystream[0:0x28] = ciphertext XOR guessed plaintext.
# ELF64 header:
#  0x00: 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
#  0x10: 02 00 b7 00 01 00 00 00  (ET_DYN=3? actually 3 for shared obj; use 03)
#  But lib may be ET_DYN (3) or ET_EXEC (2). Try both for byte 0x10 (u16 0200 or 0300)
import struct
for et in (2, 3):
    hdr = bytearray(0x28)
    hdr[0:4] = b'\x7fELF'
    hdr[4] = 2   # 64-bit
    hdr[5] = 1   # LE
    hdr[6] = 1
    struct.pack_into('<H', hdr, 0x10, et)
    struct.pack_into('<H', hdr, 0x12, 0xb7)  # aarch64
    struct.pack_into('<I', hdr, 0x14, 1)     # version
    # e_entry at 0x18 unknown, e_phoff at 0x20 = 0x40 typically, e_shoff at 0x28 unknown
    struct.pack_into('<Q', hdr, 0x20, 0x40)  # e_phoff guess
    ks = bytes(c ^ g for c, g in zip(xz[:0x28], hdr))
    print('et=%d keystream[0:0x28]: %s' % (et, ks.hex()))
    # periodicity test on longer keystream if we can extend known plaintext...
