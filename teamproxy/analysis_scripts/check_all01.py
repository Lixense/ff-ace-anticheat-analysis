import io, sys, zipfile, os

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
# locate ALL01.zip in payload_inner
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_inner\assets_ALL01.zip'
if not os.path.exists(p):
    # search
    for root, dirs, files in os.walk(r'E:\android_version\LIXCLIENT_version2\teamproxy'):
        for f in files:
            if 'ALL01' in f:
                p = os.path.join(root, f)
                print('found', p)
print('using', p)
z = zipfile.ZipFile(p)
for e in z.infolist():
    print('%s len=%d' % (e.filename, e.file_size))
