import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()
for m in re.finditer(r'/\* ===== (Java_[^ ]*onCreate[^ ]*) ==== \*/', s):
    name = m.group(1)
    j = s.find('/* =====', m.end())
    body = s[m.end():j if j >= 0 else m.end() + 3000]
    print(name, 'len', len(body))
