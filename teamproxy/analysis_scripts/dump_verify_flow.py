import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
# show method bodies that invoke 请君为我倾耳听 / verify / build signature
for part in re.split(r'(?=\.method )', s):
    mm = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if not mm:
        continue
    name = mm.group(1)
    if name in ('onCreate', '丹丘生', '将进酒', '岑夫子', '人生得意须尽欢', '古来圣贤皆寂寞', '会须一饮三百杯', '但愿长醉不复醒'):
        print('====== %s ======' % name)
        # strip array data
        lines = []
        for ln in part.split('\n'):
            if ln.strip().startswith(':array_'):
                break
            lines.append(ln)
        print('\n'.join(lines[:260]))
