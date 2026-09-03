import io, sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
enc = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc', 'rb').read()
ascii_key = b'f7a2c9d1e8b34560ac7ef1230d9b56e4'   # 32B
hex_key = bytes.fromhex(ascii_key.decode())        # 16B

combos = {
    'AES256_ctr_iv=hexkey': (ascii_key, hex_key, 'CTR'),
    'AES128_ctr_iv=hexkey': (hex_key, hex_key, 'CTR'),
    'AES256_ctr_iv=zero':   (ascii_key, b'\x00'*16, 'CTR'),
    'AES128_ctr_iv=zero':   (hex_key, b'\x00'*16, 'CTR'),
    'AES256_ctr_iv=ascii_first16': (ascii_key, ascii_key[:16], 'CTR'),
    'AES128_ctr_iv=ascii_first16': (hex_key, ascii_key[:16], 'CTR'),
    'AES256_cbc_iv=hexkey': (ascii_key, hex_key, 'CBC'),
    'AES128_cbc_iv=hexkey': (hex_key, hex_key, 'CBC'),
    'AES256_cbc_iv=zero':   (ascii_key, b'\x00'*16, 'CBC'),
    'AES128_cbc_iv=zero':   (hex_key, b'\x00'*16, 'CBC'),
}
for name, (k, iv, mode) in combos.items():
    try:
        if mode == 'CTR':
            d = Cipher(algorithms.AES(k), modes.CTR(iv)).decryptor()
        else:
            d = Cipher(algorithms.AES(k), modes.CBC(iv)).decryptor()
        pt = d.update(enc[:128])
        ok = pt[:4] == b'\x7fELF'
        print('%s: %s %s' % (name, pt[:8].hex(), '*** ELF ***' if ok else ''))
        if ok:
            full = Cipher(algorithms.AES(k), modes.CTR(iv) if mode=='CTR' else modes.CBC(iv)).decryptor()
            outp = full.update(enc) + full.finalize()
            open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so','wb').write(outp)
            print('SAVED')
    except Exception as e:
        print(name, 'err', e)
