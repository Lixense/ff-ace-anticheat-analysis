import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
xz = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc','rb').read()
qw = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libQWERTYUIOPAS.so.enc','rb').read()

n = min(len(xz), len(qw))
xor = bytes(a^b for a,b in zip(xz[:n], qw[:n]))
# count zero vs nonzero
nz = sum(1 for b in xor if b)
print('XOR nonzero bytes:', nz, '/', n, '=', round(100*nz/n,2), '%')
# If CTR same key/iv: xor = p1^p2 sparse (few %)
# If different key/iv: xor ~ random (50%)
# structure of nonzero regions:
# print runs of nonzero
runs = []
i = 0
while i < n:
    if xor[i]:
        j = i
        while j < n and xor[j]:
            j += 1
        runs.append((i, j-i))
        i = j
    else:
        i += 1
print('nonzero runs:', len(runs))
for r in runs[:40]:
    print('  run at 0x%x len %d' % r)
print('  ...')
for r in runs[-10:]:
    print('  run at 0x%x len %d' % r)
