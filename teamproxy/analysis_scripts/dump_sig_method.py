import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes4\com\Sx2\Team\Ban\君不见高堂明镜悲白发谁家今夜扁舟子何处相思明月楼َ.smali'
s = open(p, encoding='utf-8').read()
parts = re.split(r'(?=\.method )', s)
for part in parts:
    m = re.search(r'\.method\s+.*?\s([\w<>]+)\(', part)
    if m and m.group(1) == '请君为我倾耳听':
        # Print only the code portion (no array data)
        code = part.split('.end method')[0]
        # strip trailing arrays: cut at first line starting with ':array'
        lines = code.split('\n')
        out = []
        for ln in lines:
            if ln.strip().startswith(':array_'):
                break
            out.append(ln)
        print('\n'.join(out))
        break
