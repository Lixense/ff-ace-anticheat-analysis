import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发千磨万击还坚韧任尔东西南北风َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)
# Show 斗酒十千恣欢谑 and 陈王昔时宴平乐 fully (code only), to see payload argument source
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if not m:
        continue
    if m.group(1) in ('斗酒十千恣欢谑', '陈王昔时宴平乐', '但愿长醉不复醒'):
        lines = []
        for ln in part.split('\n'):
            if ln.strip().startswith(':array_'):
                break
            lines.append(ln)
        print('#### %s ####' % m.group(1))
        print('\n'.join(lines))
        print()
