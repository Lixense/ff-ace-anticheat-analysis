import sys, os, zipfile, struct
roots=[r"E:\android_version\LIXCLIENT_version2\teamproxy\com.Sx2.Team.Ban"]
zf=None
for r,d,fs in os.walk(roots[0]):
    for f in fs:
        p=os.path.join(r,f)
        if os.path.getsize(p)>1000000:
            zf=p; break
    if zf: break
print("ZIP:",zf)
z=zipfile.ZipFile(zf)
data=z.read("AndroidManifest.xml")
print("manifest bytes",len(data))
def u16(b,o): return struct.unpack_from("<H",b,o)[0]
def u32(b,o): return struct.unpack_from("<I",b,o)[0]
assert data[:4]==b"\x03\x00\x08\x00"
str_off=u32(data,8); str_count=u32(data,12)
print("string pool at",str_off,"count",str_count)
p=str_off
flags=u32(data,p+4)
utf8=(flags & 0x100)!=0
n=u32(data,p+8)
o=u32(data,p+16)
strings=[]
for i in range(n):
    q=str_off+u32(data,o+i*4)
    if utf8:
        ll=u16(data,q+2)
        s=data[q+4:q+4+ll].decode("utf-8",errors="replace")
    else:
        ll=u16(data,q+2)
        s=data[q+4:q+4+ll*2].decode("utf-16-le",errors="replace")
    strings.append(s)
for s in strings:
    print(repr(s))
