import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发千磨万击还坚韧任尔东西南北风َ.smali'
s = open(p, encoding='utf-8').read()
# Find references to these methods within the same class (invoke-direct ...->斗酒十千恣欢谑 etc)
for i, line in enumerate(s.split('\n'), 1):
    if '斗酒十千恣欢谑' in line or '陈王昔时宴平乐' in line or '但愿长醉不复醒' in line:
        print(i, line.strip()[:200])
