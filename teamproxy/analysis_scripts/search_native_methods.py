import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()
# search for unicode poem names escaped or direct
for kw in ['斗酒十千', '陈王昔时', '与君歌一曲', '但愿长醉不复醒', '千磨万击', '丹丘生', '奔流到海不复回', '君不见高堂明镜悲白发']:
    print(kw, s.count(kw))
# find calls to CallStaticObjectMethod/CallObjectMethod/CallStaticVoid etc patterns in decompiled (JNI indirect calls)
for kw in ['0x1f8', '0x200', '0x208', '0x210', '0x218', '0x228', '0x238', 'GetStringUTF', 'getStringUTF', 'NewString']:
    print(kw, s.count(kw))
