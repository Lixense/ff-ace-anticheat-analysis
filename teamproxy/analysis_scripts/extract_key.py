import re, sys

p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\smali_classes3\np\君不见高堂明镜悲白发君不见高堂明镜悲白发朝如青丝暮成雪َ.smali'
s = open(p, encoding='utf-8').read()
m = re.search(r'<clinit>.*?const-string v0, "(.*?)"\s*\n\s*sput-object', s, re.S)
if m:
    raw = m.group(1)
    key = raw.encode('utf-8').decode('unicode_escape')
    print('KEYLEN', len(key))
    open('xor_key.txt', 'w', encoding='utf-8').write(key)
    print(repr(key[:150]))
else:
    print('NO MATCH')
