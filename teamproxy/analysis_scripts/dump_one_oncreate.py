import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\java_exports_decomp.c', encoding='utf-8', errors='replace').read()
parts = re.split(r'(?=/\* ===== Java_)', s)
for p in parts:
    m = re.match(r'/\* ===== (Java_\S+ @ )', p)
    if not m:
        continue
    if '@ 0012f780 ' in p:
        print(p)
