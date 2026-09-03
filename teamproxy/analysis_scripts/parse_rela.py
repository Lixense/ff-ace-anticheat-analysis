import io, sys, struct

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# Find .rela.dyn section from section headers
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
shstr_off = sections[e_shstrndx][4]
def secname(noff):
    end = data.index(b'\x00', shstr_off + noff)
    return data[shstr_off+noff:end].decode()

rela = None
for s in sections:
    if secname(s[0]) == '.rela.dyn':
        rela = s
        print('.rela.dyn at off 0x%x size 0x%x' % (s[4], s[5]))
if rela:
    off0, size0 = rela[4], rela[5]
    n = size0 // 24
    print('entries:', n)
    # Elf64_Rela: r_offset(8) r_info(8) r_addend(8)
    rels = []
    for i in range(n):
        o = off0 + i * 24
        r_offset, r_info, r_addend = struct.unpack_from('<QQq', data, o)
        r_type = r_info & 0xffffffff
        r_sym = r_info >> 32
        # R_AARCH64_RELATIVE = 1027
        if r_type == 1027 and 0x1b000 <= (r_addend & 0xffffffffffff) <= 0x1e800:
            rels.append((r_offset, r_addend))
    print('RELATIVE relocs with addend into table:', len(rels))
    for r_offset, r_addend in rels[:120]:
        print('  GOT/ptr at vaddr 0x%x <- table 0x%x' % (r_offset, r_addend))
