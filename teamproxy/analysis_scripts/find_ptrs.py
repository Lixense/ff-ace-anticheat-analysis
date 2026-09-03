import io, sys, struct

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# .data/.bss writable segment: off=0x91710 vaddr=0x93710 (from earlier output - the type=1 flags=6 is at 0x8f340)
# Actually from ELF map: second RW LOAD: off=0x8e340 vaddr=0x8f340 (that's data, size 0x33d0)
# Scan all file for 8-byte little-endian pointers into 0x1b000-0x1e800
targets = []
for off in range(0, len(data) - 8):
    v = struct.unpack_from('<Q', data, off)[0]
    if 0x1b000 <= v <= 0x1e800:
        targets.append((off, v))
print('pointer refs into table region:', len(targets))
for off, v in targets[:60]:
    print('file off 0x%x (vaddr 0x%x) -> 0x%x' % (off, off, v))
