import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()
for m in re.finditer(r'/\* ===== (\S+) @', s):
    f = m.group(1)
    if 'onCreate' in f or 'initDcc' in f or 'h0k' in f:
        print(f)
