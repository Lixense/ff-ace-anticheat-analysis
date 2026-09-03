import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\oncreate_31198.c', encoding='utf-8', errors='replace').read()
print('total lines', s.count('\n'))
print(s[15000:40000])
