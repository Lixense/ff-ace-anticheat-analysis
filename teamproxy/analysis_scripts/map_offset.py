import io, sys, re, struct

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
# Parse ELF section headers to map file offset 0x1c3b9 -> virtual address
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()
# ELF64 header
assert data[:4] == b'\x7fELF'
e_shoff = struct.unpack_from('<Q', data, 0x28)[0]
e_shentsize = struct.unpack_from('<H', data, 0x3a)[0]
e_shnum = struct.unpack_from('<H', data, 0x3c)[0]
e_shstrndx = struct.unpack_from('<H', data, 0x3e)[0]

sections = []
for i in range(e_shnum):
    off = e_shoff + i * e_shentsize
    sh = data[off:off+e_shentsize]
    name_off, typ, flags, addr, offset, size = struct.unpack_from('<IIQQQQ', sh, 0)
    sections.append((name_off, typ, flags, addr, offset, size))

# get section name strings
shstr_off = sections[e_shstrndx][4]
def secname(noff):
    end = data.index(b'\x00', shstr_off + noff)
    return data[shstr_off+noff:end].decode()

for s in sections:
    name = secname(s[0])
    if s[5] > 0 and s[4] <= 0x1c3b9 < s[4] + s[5]:
        print('file offset 0x1c3b9 in section', name, 'addr=0x%x size=0x%x' % (s[3], s[5]))
        # VA = addr + (0x1c3b9 - offset)
        va = s[3] + (0x1c3b9 - s[4])
        print('=> VA 0x%x' % va)
