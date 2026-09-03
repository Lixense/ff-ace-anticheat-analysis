import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\java_exports_decomp.c', encoding='utf-8', errors='replace').read()
print('len', len(s))
funcs = re.findall(r'/\* ===== (Java_\S+) @', s)
print('funcs', len(funcs))
for f in funcs[:15]:
    print(f)
