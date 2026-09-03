import io, sys, struct

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()
e_phoff = struct.unpack_from('<Q', data, 0x20)[0]
e_phentsize = struct.unpack_from('<H', data, 0x36)[0]
e_phnum = struct.unpack_from('<H', data, 0x38)[0]
print('program headers:')
for i in range(e_phnum):
    off = e_phoff + i * e_phentsize
    p_type, p_flags = struct.unpack_from('<II', data, off)
    p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_align = struct.unpack_from('<QQQQQQ', data, off+8)
    print('  type=%d flags=0x%x off=0x%x vaddr=0x%x filesz=0x%x memsz=0x%x' % (p_type, p_flags, p_offset, p_vaddr, p_filesz, p_memsz))
# file offset 0x1c3b9 -> which segment? compute vaddr
for i in range(e_phnum):
    off = e_phoff + i * e_phentsize
    p_type = struct.unpack_from('<I', data, off)[0]
    p_offset, p_vaddr = struct.unpack_from('<QQ', data, off+8)
    p_filesz = struct.unpack_from('<Q', data, off+32)[0]
    if p_type == 1 and p_offset <= 0x1c3b9 < p_offset + p_filesz:
        print('file 0x1c3b9 -> vaddr 0x%x' % (p_vaddr + (0x1c3b9 - p_offset)))
