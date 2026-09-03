import io, sys, base64

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
KEYB = bytes(ord(c) & 0xff for c in KEY)
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

def arabic_static_xor_hex(hexstr):
    """Java 君不见...(String): hex decode then XOR arabic low bytes"""
    b = bytes.fromhex(hexstr)
    return bytes(c ^ KEYB[i % len(KEYB)] for i, c in enumerate(b))

def base64_of_bytes(arr):
    return base64.b64decode(arr).decode('latin1')

def xorkey(ct, key):
    return bytes(c ^ key[i % len(key)] for i, c in enumerate(ct))

# chain from onCreate 0x31198 (c15e -> c16e -> [result used as key for c1a3])
b64_15e = data[0x1c15e:0x1c15e+16].decode()          # Mjk3QTI4NDMyQjdF
hex1 = base64.b64decode(b64_15e).decode('latin1')     # 297A28432B7E
print('hex1', hex1)
key1 = arabic_static_xor_hex(hex1)
print('key1', key1)
ct_16e = data[0x1c16e:0x1c16e+5]
s1 = xorkey(ct_16e, key1)
print('s1 (result of c16e decrypt)', s1, repr(s1))

# Now: c16e decrypt was invoked via ([B,Str,ZZ) = XOR with KEY STRING key1... but wait, that call's key was
# 'v1' from earlier stage: the code did the c15e decode with 'new String(byte[])' which is PLAIN BASE64
# (the ([B)String helper) -> giving hex1 string; THEN called static XOR? Let's check: the onCreate called
# &DAT_0011a6bb (poem method) with ([B)Ljava/lang/String; on the c15e array -> that's the b64 helper
# giving hex1 string. Then it used THAT string where? Need to trace. Test: key = hex1 directly to decrypt c16e.
s1b = xorkey(ct_16e, hex1.encode('latin1'))
print('s1b (hex1 as key)', s1b, repr(s1b))

# also the code's earlier stage: after 'new String(ct_15e)' the code built a 5-byte NewByteArray and
# called ([B,Str,ZZ) with the hex1 string as key param -> s1b should be the actual s1 if key is hex1-ascii.
# If s1b is the real intermediate, feed it as key into c1a3
ct_1a3 = data[0x1c1a3:0x1c1a3+27]
for name, midkey in [('s1', s1), ('s1b', s1b)]:
    pt = xorkey(ct_1a3, midkey)
    print('decrypt c1a3 with %s -> %r' % (name, pt))
