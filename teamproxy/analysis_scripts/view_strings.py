import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_strings.txt'
try:
    s = open(p, encoding='utf-8', errors='replace').read()
    print('len', len(s))
    lines = [l for l in s.split('\n') if l.strip()]
    print('count', len(lines))
    for l in lines[:100]:
        print(l)
except Exception as e:
    print('ERR', e)
