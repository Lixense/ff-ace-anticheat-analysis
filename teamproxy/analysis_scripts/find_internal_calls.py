import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\com\Sx2\Team\Ban\君不见高堂明镜悲白发长风万里送秋雁对此可以酣高楼َ.smali'
s = open(p, encoding='utf-8').read()
# find all invoke usages of own methods to see who calls 惟有饮者留其名 / with what args
for i, line in enumerate(s.split('\n'), 1):
    if 'Lcom/Sx2/Team/Ban/君不见高堂明镜悲白发长风万里送秋雁对此可以酣高楼َ;->' in line and 'invoke' in line:
        print(i, line.strip()[:200])
