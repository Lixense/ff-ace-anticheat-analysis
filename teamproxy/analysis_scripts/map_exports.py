import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()

# The JNI-exported functions are present as FUN_* since Ghidra didn't name them.
# But their symbol names exist in the .dynsym. Let's map export name -> address from the .so,
# then find the FUN_ at that address in the decompiled C.
import struct
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# parse dynsym + dynstr
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

dynsym = dynstr = None
for s in sections:
    n = secname(s[0])
    if n == '.dynsym': dynsym = s
    if n == '.dynstr': dynstr = s

# map symbol name -> value
name_to_addr = {}
if dynsym and dynstr:
    ds_off, ds_size = dynsym[4], dynsym[5]
    dst_off = dynstr[4]
    count = ds_size // 24
    for i in range(count):
        o = ds_off + i * 24
        st_name, st_info, st_other, st_shndx, st_value, st_size = struct.unpack_from('<IBBHQQ', data, o)
        if st_name == 0: continue
        end = data.index(b'\x00', dst_off + st_name)
        nm = data[dst_off+st_name:end].decode('latin1')
        name_to_addr[nm] = st_value

# find JNI onCreate exports + h0k clinit + initDcc
for nm, addr in sorted(name_to_addr.items()):
    if 'onCreate' in nm or ('h0k' in nm and ('cinit' in nm or 'initDcc' in nm)):
        print('0x%x  %s' % (addr, nm))
