import io, sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
enc = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc', 'rb').read()
key = b'f7a2c9d1e8b34560ac7ef1230d9b56e4'  # 32B ascii = AES-256

ivs = {
    'x4Rq_x4': b'x4Rq' * 4,
    'x4Rq_pad0': b'x4Rq' + b'\x00'*12,
    'x4Rq_pad1': b'x4Rq' + b'\x01'*12,
    'x4Rq_zero_ctr': b'x4Rq' + b'\x00'*11 + b'\x01',  # maybe counter-style
    'key16_xor_x4Rq': bytes(a^b for a,b in zip(key[:16], b'x4Rq'*4)),
    'md5_x4Rq': __import__('hashlib').md5(b'x4Rq').digest(),
    'sha1_x4Rq': __import__('hashlib').sha1(b'x4Rq').digest()[:16],
}
# also try CBC (maybe the string says CTR but server uses CBC)
from cryptography.hazmat.primitives.ciphers import Cipher as C2
for name, iv in ivs.items():
    for mode_name in ('CTR', 'CBC'):
        try:
            if mode_name == 'CTR':
                d = Cipher(algorithms.AES(key), modes.CTR(iv)).decryptor()
            else:
                d = Cipher(algorithms.AES(key), modes.CBC(iv)).decryptor()
            pt = d.update(enc[:64])
            ok = pt[:4] == b'\x7fELF'
            print('%s %s: %s %s' % (name, mode_name, pt[:8].hex(), '*** ELF ***' if ok else ''))
        except Exception as e:
            print(name, mode_name, 'err', e)
