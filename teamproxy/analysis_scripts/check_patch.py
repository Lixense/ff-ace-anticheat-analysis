import io, sys, os, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes'
data = open(p, 'rb').read()
print('size', len(data))
print('head hex:', data[:64].hex(' '))
print('head ascii:', ''.join(chr(c) if 32 <= c < 127 else '.' for c in data[:64]))
# scan for .NET/unity signatures
for sig in [b'BSJB', b'\x00\x01\x00\x00\x00\xff\xff\xff\xff', b'Assembly-CSharp', b'mscorlib', b'UnityEngine']:
    i = data.find(sig)
    print(sig, 'at', hex(i) if i >= 0 else 'not found')
# printable strings
strs = re.findall(rb'[\x20-\x7e]{6,}', data)
print('--- strings (%d) ---' % len(strs))
for s in strs[:80]:
    print(repr(s.decode('latin1')))
