import io, sys, os

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
d = r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes'
files = {}
for f in os.listdir(d):
    if f.endswith('Assembly-CSharp-patch.bytes'):
        files[f] = open(os.path.join(d, f), 'rb').read()

a = files['ALL01_1F_Assembly-CSharp-patch.bytes']
for name in sorted(files):
    data = files[name]
    print('=== %s ===' % name)
    # print context around byte 19940-19990
    for i in range(19940, 19990):
        if i < len(data):
            ch = chr(data[i]) if 32 <= data[i] < 127 else '.'
        else:
            ch = ' '
        mark = ''
        if i >= len(a) or a[i] != data[i]:
            mark = '<'
        print('%5d %3d %s %s' % (i, data[i], ch, mark))
    print()
