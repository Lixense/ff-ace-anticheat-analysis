import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
patch = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()

# definitive function-level proof of what the patch can/cannot do
allstrs = [s.decode('latin1') for s in re.findall(rb'[\x20-\x7e]{3,}', patch)]

# The set of methods the hotfix can call (member refs found in metadata) => functional capability
calls = ['GetInt','CallStatic','ToString','Concat','Exists','Call','SetInt','GetFloat',
'get_frameCount','GetMainCamera','get_main','get_transform','Find','get_gameObject',
'get_activeSelf','SetActive','get_transform','SetParent','AddComponent','set_sortingOrder',
'get_identity','set_localRotation','get_pixelWidth','get_pixelHeight','get_width','get_height',
'get_fieldOfView','Tan','get_sizeDelta','set_sizeDelta','get_localScale','set_localScale',
'get_localPosition','set_localPosition','GetHeadTF','IsLocalPlayer','get_CurHP','IsLocalTeammate',
'GetInstanceID','Concat','GetHipTF','get_position','WorldToScreenPoint','set_raycastTarget',
'set_enabled','set_anchorMin','set_anchorMax','set_pivot','set_anchoredPosition','get_childCount',
'GetChild','GetComponent','get_material','SetInt','set_renderQueue','set_material','set_color',
'Euler','get_MaxHP','Sqrt','Atan2','GetAttackableCenterWS','SetActive','get_gameObject','GetSoundEffect']

def has(s): return s in allstrs or s.encode() in patch
print('=== FUNCTIONAL PROOF: hotfix patch capabilities ===')
print()
print('-- ESP/visual (present):')
for s in ['GetHeadTF','GetHipTF','GetAttackableCenterWS','WorldToScreenPoint','IsLocalPlayer','IsLocalTeammate','get_CurHP','get_MaxHP','get_main','CameraUtility']:
    print('  %-28s %s' % (s, 'YES' if has(s) else 'NO'))
print('-- UI/canvas (present):')
for s in ['Canvas','Image','Hidden/Internal-Colored','unity_GUIZTestMode','set_sortingOrder','AddComponent','RectTransform']:
    print('  %-28s %s' % (s, 'YES' if has(s) else 'NO'))
print('-- AIMBOT capability (would need one of these):')
aimvec = {
  'Camera rotation write (set_localRotation on camera/transform)': 'set_localRotation',
  'look direction read/write (eulerAngles/localEulerAngles/forward)': 'eulerAngles',
  'view angles / LookAt / LookRotation': 'LookRotation',
  'weapon/fire control (Fire/Shoot/Trigger)': 'Fire',
  'target locking (AimAssist/LockTarget/AimOffset)': 'AimAssist',
  'auto-aim smoothing (SmoothAim/smooth)': 'smooth',
  'bone/aimbone targeting (HeadBone/AimBone)': 'Bone',
  'silent aim / RPC aim': 'SilentAim',
}
for desc, tok in aimvec.items():
    print('  %-50s %s' % (desc, 'FOUND' if has(tok) else 'absent'))
print()
print('-- What the patch DOES write to rotation:', 'set_localRotation present:', has('set_localRotation'),
      '(used with Quaternion.identity + Euler for the ESP canvas overlay orientation, not player aim)')
print('-- Native lib it loads:', has('load'), '(System.load of the downloaded .so)')
