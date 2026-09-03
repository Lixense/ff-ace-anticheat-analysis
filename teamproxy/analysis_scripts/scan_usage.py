import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
BASE = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled'
# Where are the sx2lador URLs + user_key/device used? search all Sx2 smali for these tokens
import os
for dex in ['smali_classes3', 'smali_classes4', 'smali_classes5']:
    d = os.path.join(BASE, dex, 'com', 'Sx2', 'Team', 'Ban')
    if not os.path.isdir(d):
        continue
    for fn in sorted(os.listdir(d)):
        if not fn.endswith('.smali'):
            continue
        p = os.path.join(d, fn)
        s = open(p, encoding='utf-8').read()
        hits = []
        for tok in ['sx2lador', 'user_key', 'device_id', 'Shizuku;->', 'RequestNetwork', 'api_key']:
            if tok in s:
                hits.append(tok)
        if hits:
            print(os.path.basename(fn), '->', ','.join(sorted(set(hits))))
