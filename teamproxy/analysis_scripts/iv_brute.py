import io, sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
enc = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc', 'rb').read()
key_ascii = b'f7a2c9d1e8b34560ac7ef1230d9b56e4'

# if plaintext were ELF: \x7fELF + 2byte class/data(usually \x01\x01) + padding
# derive keystream block0 = ct ^ pt_guess
guess = b'\x7fELF\x01\x01\x01' + b'\x00' * 9  # 16-byte guess for ELF64 little-endian
ks0 = bytes(c ^ g for c, g in zip(enc[:16], guess))
print('derived keystream0:', ks0.hex())
# The first 16 bytes of CTR keystream = AES-ECB(key, IV). Brute-force common IV values by
# comparing AES(key, candidate_iv) == ks0
import itertools
cands = {
    'zero': b'\x00' * 16,
    'key16a': key_ascii[:16],
    'key16b': key_ascii[16:],
    'classic_md5': None,
}
# Also derive what IV would produce ks0 by checking keystream vs AES(key, IV||counter)
# AES-CTR uses IV as the initial counter block (16 bytes big-endian counter).
def aes_ecb(k, block):
    c = Cipher(algorithms.AES(k), modes.ECB()).encryptor()
    return c.update(block) + c.finalize()

for name, iv in cands.items():
    if iv is None: continue
    print(name, 'match' if aes_ecb(key_ascii, iv) == ks0 else 'no')
# brute force small/structured IVs: 16-byte IVs where it's an ASCII string from the patch metadata
import re
patch = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()
strs = re.findall(rb'[\x20-\x7e]{4,}', patch)
for s in strs:
    if len(s) >= 16 and aes_ecb(key_ascii, s[:16]) == ks0:
        print('IV = string', s[:16])
