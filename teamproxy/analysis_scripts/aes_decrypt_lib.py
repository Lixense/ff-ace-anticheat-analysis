import io, sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
enc = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc', 'rb').read()

key_ascii = b'f7a2c9d1e8b34560ac7ef1230d9b56e4'  # 32B AES-256
candidates = {
    'zero_iv': b'\x00' * 16,
    'key_first16': key_ascii[:16],
    'key_last16': key_ascii[16:],
}
for name, iv in candidates.items():
    try:
        dec = Cipher(algorithms.AES(key_ascii), modes.CTR(iv)).decryptor()
        pt = dec.update(enc) + dec.finalize()
        print('%s: first16=%s  ELF? %s' % (name, pt[:16].hex(), pt[:4] == b'\x7fELF'))
        if pt[:4] == b'\x7fELF':
            open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so', 'wb').write(pt)
            print('saved decrypted')
    except Exception as e:
        print(name, 'error', e)
