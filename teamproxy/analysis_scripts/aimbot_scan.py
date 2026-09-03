import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes'
data = open(p, 'rb').read()

# 1) all printable tokens
strs = re.findall(rb'[\x20-\x7e]{4,}', data)

# 2) aim/weapon/lock-related case-insensitive search
pats = [b'aim', b'lock', b'lookat', b'fire', b'shoot', b'bullet', b'weapon',
        b'angle', b'euler', b'rotation', b'headshot', b'trigger', b'bone',
        b'silent', b'fov', b'distance', b'smooth', b'target']
print('=== aim-related token scan ===')
for s in strs:
    low = s.lower()
    for pat in pats:
        if pat in low:
            print('%r  (match: %s)' % (s.decode('latin1'), pat.decode()))
            break

# 3) count tokens containing typical ESP vs aim vocabulary
esp_tok = [b'__ebox', b'__ehead', b'__eline', b'__ehp', b'__efull', b'WorldToScreen', b'GetHeadTF']
aim_tok = [b'AimAssist', b'LockTarget', b'LookAt', b'eulerAngles', b'localEulerAngles', b'AutoFire', b'get_forward']
for t in esp_tok: print('ESP token %s: %d occurrences' % (t.decode(), data.count(t)))
for t in aim_tok: print('AIM token %s: %d occurrences' % (t.decode(), data.count(t)))
