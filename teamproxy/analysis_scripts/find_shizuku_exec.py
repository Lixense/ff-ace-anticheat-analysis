import io, sys, os

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
BASE = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled'
# Only Sx2/Team/Ban classes across dexes
roots = []
for dex in ['smali_classes3', 'smali_classes4', 'smali_classes5']:
    p = os.path.join(BASE, dex, 'com', 'Sx2', 'Team', 'Ban')
    if os.path.isdir(p):
        roots.append(p)
for root in roots:
    for fn in sorted(os.listdir(root)):
        if not fn.endswith('.smali'):
            continue
        p = os.path.join(root, fn)
        s = open(p, encoding='utf-8').read()
        # count occurrences of the shizuku exec call sig
        import re
        m = re.findall(r'Lrikka/shizuku/Shizuku;->([\w]+)\(\[Ljava/lang/String', s)
        if m:
            print(os.path.relpath(p, BASE), '-> exec calls:', m)
