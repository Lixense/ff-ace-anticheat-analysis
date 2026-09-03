import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\java_exports_decomp.c', encoding='utf-8', errors='replace').read()
out = []
# split by function headers
parts = re.split(r'(?=/\* ===== Java_)', s)
for p in parts:
    m = re.match(r'/\* ===== (Java_\S+) @', p)
    if not m:
        continue
    nm = m.group(1)
    if 'onCreate' in nm or ('h0k' in nm) or 'onResume' in nm:
        out.append('##### ' + nm + ' #####')
        out.append(p)
with open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\oncreate_funcs.c', 'w', encoding='utf-8') as fh:
    fh.write('\n'.join(out))
print('wrote oncreate_funcs.c', len(out), 'parts')
