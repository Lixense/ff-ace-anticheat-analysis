import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so', 'rb').read()

# find the big encrypted blob strings and their file offsets
blobs = [
    b'UNzY3RDc0MTQ3Rjcz',
    b'1)-kg~7Nzc3QTc4NDQyRjJE',
    b'SUTUN0Q3RjJBNDIyRjdD',
    b'MkU3QjJFNDA3OTJE',
    b'N0Y3QTI5MTE3QTdDQX',
]
for b in blobs:
    idx = data.find(b)
    print(b[:20], 'at file offset', hex(idx) if idx >= 0 else 'NOT FOUND')

# Also dump raw rodata section around those offsets to capture full blob context
idx = data.find(b'UNzY3RDc0MTQ3Rjcz')
if idx >= 0:
    chunk = data[idx-64:idx+400]
    print('context:', repr(chunk))
