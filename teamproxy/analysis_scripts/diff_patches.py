import io, sys, os, re, hashlib

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
d = r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes'
files = {}
for f in os.listdir(d):
    p = os.path.join(d, f)
    data = open(p, 'rb').read()
    files[f] = data
    print(f, len(data), hashlib.md5(data).hexdigest())
# diff 1F vs 2F vs 3F vs 4F
a = files['ALL01_1F_Assembly-CSharp-patch.bytes']
for f, data in files.items():
    if f.endswith('Assembly-CSharp-patch.bytes') and f != 'ALL01_1F_Assembly-CSharp-patch.bytes':
        # find differing bytes
        diffs = [(i, a[i], data[i]) for i in range(min(len(a), len(data))) if a[i] != data[i]]
        print(f, 'vs 1F: diffs', len(diffs), diffs[:20])

# dump ALL strings from the 1F patch
strs = re.findall(rb'[\x20-\x7e]{4,}', a)
print('--- ALL strings (%d) ---' % len(strs))
for s in strs:
    print(repr(s.decode('latin1')))
