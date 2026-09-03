import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()
for kw in ['JNI_OnLoad', 'RegisterNatives', 'Java_com_Sx2', 'GetStringUTFChars', 'NewStringUTF', 'CallVoidMethod', 'CallStaticVoidMethod', 'GetMethodID', 'GetStaticMethodID']:
    print(kw, s.count(kw))
i = s.find('JNI_OnLoad')
if i >= 0:
    print(s[max(0, i-200):i+3000])
