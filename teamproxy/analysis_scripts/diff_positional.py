import io, sys, struct

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
xz = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc','rb').read()
qw = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libQWERTYUIOPAS.so.enc','rb').read()

# The two files match except at 0x28 (one byte). That means ENCRYPTION IS POSITIONAL (same keystream)
# and plaintexts differ only at 0x28. If these were .so with a mode-name embedded, the name is at
# a FIXED offset => XZ plaintext has 'XZAXZAXZAXZA', QW has 'QWERTYUIOPAS' at same offset => many diffs.
# But we see only 1 diff => the mode name is NOT in the binary; the 1-byte diff at 0x28 is likely
# e_machine? no (0x28 is in e_flags/e_version region? ELF: e_version at 0x14...)
# Actually for a 64-bit ELF header:
#  0  e_ident[16]
# 16  e_type(2) e_machine(2) e_version(4) = bytes 16..24
# 24  e_entry(8) = bytes 24..32   <-- 0x28 = byte 40 = e_phoff LOW byte region? e_phoff at 32..40, e_shoff at 40..48
# 0x28 = 40 decimal = e_shoff byte0. Both files have e_shoff differing by 0x30? 
# Wait: maybe not ELF headers at all. Let's directly test the "single-byte XOR keystream" hypothesis:
# if keystream = repeating key K, then (xz[i]^qw[i]) = (px[i]^pq[i]) which is 0 everywhere except 0x28
diffs = [i for i in range(min(len(xz),len(qw))) if xz[i]!=qw[i]]
print('num diffs:', len(diffs), 'first 20:', [hex(i) for i in diffs[:20]])
