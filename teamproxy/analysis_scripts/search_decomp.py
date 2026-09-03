import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
s = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c', encoding='utf-8', errors='replace').read()
print('total len', len(s))
for kw in ['localconfig', 'reporf', 'Assembly-CSharp', 'UnityShader', 'SX222', 'freefire', 'hidden', 'com.dts', 'ALL01', 'files/', 'cache/']:
    hits = [m.start() for m in re.finditer(re.escape(kw), s)]
    print(kw, len(hits))
