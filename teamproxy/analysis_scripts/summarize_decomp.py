import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()
funcs = re.findall(r'/\* ===== (\S+) @', s)
print('total funcs', len(funcs))
for kw in ['Java', 'JNI', 'onCreate', 'Shizuku', 'exec', 'Exec', 'RequestNetwork', 'h0k', 'cinit', 'Run', 'run', 'initDcc', 'native']:
    c = sum(1 for f in funcs if kw in f)
    print(kw, c)
