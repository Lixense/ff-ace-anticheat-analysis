import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
KEY = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\xor_key.txt', encoding='utf-8').read()
print('len', len(KEY))
cp = [hex(ord(c)) for c in KEY[:40]]
print(cp)
uniq = set(KEY)
print('uniq chars', len(uniq))
print([hex(ord(c)) for c in sorted(uniq)][:60])
