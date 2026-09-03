import io, sys, os

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
BASE = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled'
TARGETS = ['惟有饮者留其名', '千岩万壑路不定迷花倚石忽已暝']
for root, dirs, files in os.walk(BASE):
    for fn in files:
        if not fn.endswith('.smali'):
            continue
        p = os.path.join(root, fn)
        try:
            s = open(p, encoding='utf-8').read()
        except Exception:
            continue
        for t in TARGETS:
            if t in s:
                rel = os.path.relpath(p, BASE)
                n = s.count(t)
                print('%s  (%dx) %s' % (rel, n, t))
