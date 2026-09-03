import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()
funcs = re.split(r'(?=/\* ===== )', s)
hits = []
for f in funcs:
    if len(f) < 2000:
        continue
    if f.count('^') >= 4 and ('DAT_' in f or 'char' in f or 'byte' in f):
        m = re.match(r'/\* ===== (\S+) @', f)
        name = m.group(1) if m else '?'
        hits.append((name, len(f), f.count('^'), f.count('DAT_')))
for h in sorted(hits, key=lambda x: -x[1])[:40]:
    print(h)
