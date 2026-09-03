import io, sys, re

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
p = r'E:\android_version\LIXCLIENT_version2\teamproxy\decompiled\lib\arm64-v8a\lib123.so'
data = open(p, 'rb').read()
# ascii strings >= 5
strs = re.findall(rb'[\x20-\x7e]{5,}', data)
keywords = [b'freefire', b'free_fire', b'dts', b'.json', b'.db', b'.bytes', b'shader', b'UnityShader',
            b'localconfig', b'reporf', b'Assembly', b'hidden', b'project', b'sdcard', b'emulated',
            b'sx2', b'SX2', b'http', b'php', b'verify', b'get_key', b'Shizuku', b'shizuku',
            b'Runtime', b'exec', b'su ', b'chmod', b'mkdir', b'echo', b'cp ', b'user_key',
            b'api_key', b'secret', b'Hmac', b'%s', b'%d', b'token', b'device', b'android_id',
            b'imei', b'cmd ', b'pm ', b'am ']
seen = set()
for s in strs:
    low = s.lower()
    if any(k in low for k in keywords):
        if s not in seen:
            seen.add(s)
            print(repr(s.decode('latin1')))
