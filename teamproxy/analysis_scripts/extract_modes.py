import io, sys, zipfile, os, json

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_inner\assets_ALL01.zip'
outdir = r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes'
os.makedirs(outdir, exist_ok=True)
z = zipfile.ZipFile(p)
for e in z.infolist():
    if e.is_dir():
        continue
    data = z.read(e.filename)
    # flatten name
    flat = e.filename.replace('/', '_')
    with open(os.path.join(outdir, flat), 'wb') as f:
        f.write(data)
    if e.filename.endswith('.json'):
        print('=== %s ===' % e.filename)
        print(data.decode('utf-8', errors='replace'))
print('--- extracted to', outdir)
