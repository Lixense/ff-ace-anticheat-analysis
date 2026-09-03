import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\java_exports_decomp.c', encoding='utf-8', errors='replace').read()
parts = re.split(r'(?=/\* ===== Java_)', s)
for p in parts:
    if '@ 00131198 ' in p:
        print(p)
