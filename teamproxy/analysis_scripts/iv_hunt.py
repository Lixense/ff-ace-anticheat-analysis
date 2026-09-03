import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()

# 1) all hex-ish runs anywhere
for m in re.finditer(rb'[0-9a-fA-F]{8,}', data):
    s = m.group(0).decode()
    print('hex @0x%04x: %s' % (m.start(), s))

# 2) all strings containing IV-ish names or repeated patterns
for m in re.finditer(rb'[\x20-\x7e]{3,}', data):
    s = m.group(0).decode('latin1')
    if re.search(r'(iv|Iv|IV|x4Rq|Rq)', s) and len(s) < 60:
        print('str  @0x%04x: %r' % (m.start(), s))
