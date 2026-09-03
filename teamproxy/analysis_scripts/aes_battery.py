import io, sys, re, hashlib
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
enc = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc', 'rb').read()
patch = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()

ascii_key = b'f7a2c9d1e8b34560ac7ef1230d9b56e4'   # 32B
hex_key   = bytes.fromhex(ascii_key.decode())      # 16B

# 1) UTF-16LE printable strings in the patch (candidate IV could be a .NET UTF-16 ldstr)
u16 = []
for m in re.finditer(rb'(?:[\x20-\x7e]\x00){6,}', patch):
    s = m.group(0).decode('utf-16le')
    u16.append(s)
print('=== UTF-16 strings in patch (%d) ===' % len(u16))
for s in u16:
    print(repr(s))
print()

# 2) AES battery
def try_dec(key, iv):
    try:
        pt = Cipher(algorithms.AES(key), modes.CTR(iv)).decryptor().update(enc)
        return pt
    except Exception as e:
        return None

keys = {'k32_ascii': ascii_key, 'k16_hex': hex_key}
ivs = {}
for kn, k in keys.items():
    ivs.update({
        '%s_zero' % kn: b'\x00'*16,
        '%s_key16a' % kn: k[:16] if len(k)>=16 else None,
        '%s_key16b' % kn: k[16:32] if len(k)>=32 else None,
        '%s_md5' % kn: hashlib.md5(k).digest(),
        '%s_sha1' % kn: hashlib.sha1(k).digest()[:16],
        '%s_asciikey16' % kn: ascii_key[:16],
    })
for name, iv in ivs.items():
    if iv is None: continue
    pt = try_dec(keys[name.split('_')[0] + '_' + name.split('_')[1]], iv) if False else None
    # simpler: iterate pairs
for kn, k in keys.items():
    for ivn, iv in list(ivs.items()):
        if not ivn.startswith(kn): continue
        pt = try_dec(k, iv)
        if pt and pt[:4] == b'\x7fELF':
            print('*** ELF DECRYPTED with %s %s' % (kn, ivn))
            open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so', 'wb').write(pt)
        elif pt:
            print('%s %s -> first8 %s' % (kn, ivn, pt[:8].hex()))
