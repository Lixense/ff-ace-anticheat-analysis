import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()

# Enumerate every method-name string (member refs) to classify aim vs esp vs ui vs download
# .NET member refs appear as plain names in metadata #Strings heap
strs = re.findall(rb'[\x20-\x7e]{3,}', data)
names = [s.decode('latin1') for s in strs]

# Getter/setter & callable members = real code paths
members = [n for n in names if re.fullmatch(r'(get_|set_)?[A-Za-z][A-Za-z0-9_]*', n)]
print('=== member-like tokens (%d) ===' % len(members))
print(', '.join(members))
print()

# Look for any rotation-writing / look-at / view-direction members
aim_indicators = ['LookAt','LookRotation','Rotate','eulerAngles','localEulerAngles','forward',
                  'right','up','Aim','AimOffset','Fire','Shoot','Trigger','HeadShot','Critical',
                  'lock','Lock','target','Target']
print('=== aim-like member hits ===')
hits = [m for m in members if any(a.lower() in m.lower() for a in aim_indicators)]
print(hits if hits else 'NONE')
print()

# PlayerPrefs key set = features user can toggle
prefs = [n for n in names if n.startswith('__') or n in ('gfx_cache_v','SoundEffect','resetGuest','testCodePatch')]
print('=== playerprefs/toggle keys ===')
print(prefs)
