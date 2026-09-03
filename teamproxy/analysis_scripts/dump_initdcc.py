import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()
i = s.find('Java_com_Sx2_Team_Ban_h0k_initDcc__')
if i >= 0:
    j = s.find('/* =====', i + 10)
    print(s[i:j][:6000])
else:
    print('not found')
