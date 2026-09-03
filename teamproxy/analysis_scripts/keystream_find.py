import io, sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
# All 3 server files share the same first 4 bytes a973775f => same cipher+IV+key (same keystream start)
# That means IV is constant. XZ and ZZ are byte-identical (same size 632040 & same header),
# QW differs in size (644632) => different content but same keystream.
import hashlib
xz = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc','rb').read()
zz = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libZZZZZZZZZZZZ.so.enc','rb').read()
qw = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libQWERTYUIOPAS.so.enc','rb').read()
print('XZ==ZZ identical?', xz == zz, hashlib.md5(xz).hexdigest(), hashlib.md5(qw).hexdigest())
print('XZ first 64:', xz[:64].hex())
print('QW first 64:', qw[:64].hex())
# If CTR: same IV+key => same keystream. QW[0:4]==XZ[0:4] confirmed => same first 16B plaintext.
# A .so's first 16 bytes are ELF header: 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 (arm64 LE)
elf_hdr16 = bytes.fromhex('7f454c46020101000000000000000000')
ks = bytes(c ^ g for c, g in zip(xz[:16], elf_hdr16))
print('keystream0:', ks.hex())
# keystream0 = AES-ECB(key, IV). key candidates: ascii32 / hex16
def aes_ecb(k, b):
    return Cipher(algorithms.AES(k), modes.ECB()).encryptor().update(b)
for kn, k in [('ascii32', b'f7a2c9d1e8b34560ac7ef1230d9b56e4'), ('hex16', bytes.fromhex('f7a2c9d1e8b34560ac7ef1230d9b56e4'))]:
    print(kn, 'lens ok', len(k))
# So find IV such that AES(key,IV)=ks. If key=ascii32 (AES-256) then IV is unknown 16B; brute common:
cands = {
 'x4Rq_x4': b'x4Rq'*4, 'x4Rq_zero': b'x4Rq'+b'\x00'*12, 'x4Rq_01': b'x4Rq'+b'\x01'*12,
 'hexkey16': bytes.fromhex('f7a2c9d1e8b34560ac7ef1230d9b56e4'),
 'ascii_first16': b'f7a2c9d1e8b34560', 'ascii_last16': b'ac7ef1230d9b56e4',
 'zero16': b'\x00'*16,
}
for kn, k in [('ascii32', b'f7a2c9d1e8b34560ac7ef1230d9b56e4'), ('hex16', bytes.fromhex('f7a2c9d1e8b34560ac7ef1230d9b56e4'))]:
    for ivn, iv in cands.items():
        if aes_ecb(k, iv) == ks:
            print('*** FOUND', kn, ivn, '=> decrypting')
            d = Cipher(algorithms.AES(k), modes.CTR(iv)).decryptor()
            pt = d.update(xz) + d.finalize()
            open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so','wb').write(pt)
            print('saved', pt[:16])
print('done')
