import io, sys, re
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

key = b'f7a2c9d1e8b34560ac7ef1230d9b56e4'  # 32 hex chars = 16 bytes ASCII? no -- used as java.lang.String.getBytes() => ascii bytes of the hex string
# In the patch: new SecretKeySpec("f7a2c9d1e8b34560ac7ef1230d9b56e4".getBytes(), "AES")
# getBytes() = UTF-8 of the 32-char ASCII string => 32 bytes. AES key must be 16/24/32.
# So key = the ASCII string itself, 32 bytes = AES-256. IV = IvParameterSpec(...) built from?
# The strings list showed only one 'java.lang.String f7a2c9d1e8b34560ac7ef1230d9b56e4' (the key) and
# IvParameterSpec class string. IV likely also from a hex string stored nearby -- scan metadata region.

key_bytes = key  # 32 ASCII bytes => AES-256

# scan patch strings near IvParameterSpec for a 16-byte / 32-hex IV candidate
patch = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()
cands = re.findall(rb'[0-9a-fA-F]{16,64}', patch)
print('hex candidates in patch:', [c.decode() for c in cands[:40]])

iv_candidates = [c for c in cands if len(c) in (32, 16, 24)]
print('iv candidates:', [c.decode() for c in iv_candidates])
