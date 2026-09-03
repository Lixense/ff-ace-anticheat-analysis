import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()
strs = re.findall(rb'[\x20-\x7e]{4,}', data)
print('total strings', len(strs))
interesting = []
for s in strs:
    low = s.lower()
    if any(k in low for k in [b'{', b'aim', b'head', b'skin', b'weapon', b'wall', b'speed', b'config', b'secret', b'token', b'sign', b'device', b'.php', b'http']):
        interesting.append(s)
for s in interesting[:200]:
    print(repr(s.decode('latin1')))
