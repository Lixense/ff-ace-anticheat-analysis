import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\com\Sx2\Team\Ban\君不见高堂明镜悲白发弃我去者昨日之日不可留َ.smali'
s = open(p, encoding='utf-8').read()
refs = sorted(set(re.findall(r'L(np/[^;]+);', s)))
for r in refs:
    print(r)
