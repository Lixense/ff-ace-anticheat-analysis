import io, sys, struct

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
xz = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc','rb').read()
qw = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libQWERTYUIOPAS.so.enc','rb').read()

# parse ELF header from offset 0 as if plaintext
if xz[:4] == b'\x7fELF':
    print('already ELF!')
else:
    # check if maybe the file is plaintext ELF with corrupted first bytes only
    print('not ELF at 0; check class at [4]:', xz[4:8].hex())
# Maybe it IS a valid ELF but with .text/.rodata XORed. Check e_ident/e_type/e_machine
# If bytes 16-18 = e_type (2) and 18-20 = e_machine (0xb7) => headers intact
print('xz[16:20]', xz[16:20].hex(), 'expect 0200 b700 for ET_DYN arm64 (LE)')
print('xz[40:52] (e_entry etc)', xz[40:52].hex())
# Let's treat bytes 0x00+ as ELF and see how far structure is valid:
# e_phoff at 32 (8B), e_shoff at 40 (8B)
phoff = struct.unpack_from('<Q', xz, 32)[0]
shoff = struct.unpack_from('<Q', xz, 40)[0]
print('e_phoff', hex(phoff), 'e_shoff', hex(shoff), 'file size', hex(len(xz)))
if phoff and phoff < len(xz) and shoff and shoff < len(xz):
    print('looks like valid ELF offsets!')
    # e_phentsize at 54, e_phnum at 56
    print('e_phentsize', struct.unpack_from('<H', xz, 54)[0], 'e_phnum', struct.unpack_from('<H', xz, 56)[0])
# compare divergence point XZ vs QW
div = next((i for i in range(min(len(xz), len(qw))) if xz[i] != qw[i]), None)
print('first divergence at', hex(div) if div else 'none', 'context:')
for i in range(div-8, div+24):
    print('%5x: xz=%02x qw=%02x %s %s' % (i, xz[i], qw[i], chr(xz[i]) if 32<=xz[i]<127 else '.', chr(qw[i]) if 32<=qw[i]<127 else '.'))
