import io, sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
xz = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc','rb').read()

def aes_ecb(k, b):
    return Cipher(algorithms.AES(k), modes.ECB()).encryptor().update(b)

# Assume plaintext[0:0x28] = ELF header + first fields (identical across libs).
# Recover keystream bytes 0..0x28 by XOR with standard ELF64 header:
# 00: 7f 45 4c 46 02 01 01 00   (ELF64 LE)
# 08: 00 00 00 00 00 00 00 00
# 10: 03 00 b7 00 01 00 00 00   (ET_DYN, AArch64, version 1)
# 18: entry? -- actually differs per lib! not identical
# So only bytes 0..0x17 are reliably identical (e_type/e_machine/e_version).
elf_prefix = bytes.fromhex('7f454c460201010000000000000000000300b70001000000')
ks = bytes(c ^ g for c, g in zip(xz[:len(elf_prefix)], elf_prefix))
print('keystream[0:24]:', ks.hex())
# In CTR, ks[0:16] = AES(key,IV), ks[16:32] = AES(key,IV+1)
# Candidate keys
keys = {
  'ascii32': b'f7a2c9d1e8b34560ac7ef1230d9b56e4',
  'hex16': bytes.fromhex('f7a2c9d1e8b34560ac7ef1230d9b56e4'),
}
# Candidate IVs from recovered ks0 = AES(key,IV): can't invert AES; instead test IVs where IV+1
# produces ks1 given key. Try the obvious: IV=ks? no. Brute common small/derived:
import itertools, hashlib
iv_cands = {
  'zero': b'\x00'*16,
  'x4Rq_x4': b'x4Rq'*4,
  'ascii16a': b'f7a2c9d1e8b34560',
  'hexkey16': bytes.fromhex('f7a2c9d1e8b34560ac7ef1230d9b56e4'),
}
ks0 = ks[:16]; ks1 = ks[16:24]  # partial second block
for kn, k in keys.items():
    for ivn, iv in iv_cands.items():
        b0 = aes_ecb(k, iv)
        ctr1 = (int.from_bytes(iv,'big')+1).to_bytes(16,'big')
        b1 = aes_ecb(k, ctr1)
        if b0 == ks0:
            print('*** KEY/IV FOUND', kn, ivn)
        if b0[:8] == ks0[:8]:
            print('partial match', kn, ivn, b0[:8].hex())
