import re, io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\com\Sx2\Team\Ban\君不见高堂明镜悲白发长风万里送秋雁对此可以酣高楼َ.smali'
s = open(p, encoding='utf-8').read()
for m in re.finditer(r':array_(\w+)\s*\n(.*?)\n\s*\.end array-data', s, re.S):
    lab = m.group(1)
    body = m.group(2)
    vals = re.findall(r'0x([0-9a-fA-F]{2})t', body)
    if vals:
        print('array_' + lab, ''.join(vals))
