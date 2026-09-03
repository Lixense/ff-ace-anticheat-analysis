import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()
# The rodata VA would appear as DAT_0011c3b9 or similar in decompiler output; check all DAT_ refs near 0x1c3xx
refs = set(re.findall(r'DAT_00(1c3[0-9a-fA-F]{2})', s))
print('DAT refs in 0x1c3xx:', sorted(refs))
# Find which function(s) reference the blob start address 0x1c3b9
for m in re.finditer(r'001c3b9|DAT_0011c3b9|0011c3b9', s):
    a = max(0, m.start()-2000)
    # find enclosing function header
    fh = s.rfind('/* =====', 0, m.start())
    print('...ref in:', s[fh:fh+80].split('@')[0].strip())
