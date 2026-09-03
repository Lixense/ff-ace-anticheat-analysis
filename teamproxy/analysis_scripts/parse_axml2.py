import os, zipfile, struct, sys

roots = [r'E:\android_version\LIXCLIENT_version2\teamproxy\com.Sx2.Team.Ban']
zf = None
for r, d, fs in os.walk(roots[0]):
    for f in fs:
        p = os.path.join(r, f)
        if os.path.getsize(p) > 1000000:
            zf = p
            break
    if zf:
        break
data = zipfile.ZipFile(zf).read('AndroidManifest.xml')


def u16(b, o):
    return struct.unpack_from('<H', b, o)[0]


def u32(b, o):
    return struct.unpack_from('<I', b, o)[0]


print('total', len(data), data[:4].hex())
pos = 8
while pos + 8 <= len(data):
    typ = u16(data, pos)
    hdr = u16(data, pos + 2)
    size = u32(data, pos + 4)
    print('chunk type=%04x size=%d at %d' % (typ, size, pos))
    if typ == 1:  # string pool
        flags = u32(data, pos + 12)
        n = u32(data, pos + 16)
        so = u32(data, pos + 24)
        utf8 = (flags & 0x100) != 0
        print('flags=%x n=%d utf8=%s' % (flags, n, utf8))
        st = pos + so
        out = []
        for i in range(n):
            off = u32(data, pos + 28 + i * 4)
            q = st + off
            if utf8:
                l1 = data[q]
                q2 = q + 1
                if l1 & 0x80:
                    l1 = ((l1 & 0x7f) << 8) | data[q2]
                    q2 += 1
                l2 = data[q2]
                q3 = q2 + 1
                if l2 & 0x80:
                    l2 = ((l2 & 0x7f) << 8) | data[q3]
                    q3 += 1
                s = data[q3:q3 + l2].decode('utf-8', errors='replace')
            else:
                l1 = u16(data, q)
                l2 = u16(data, q + 2)
                s = data[q + 4:q + 4 + l2 * 2].decode('utf-16-le', errors='replace')
            out.append(s)
        with open('manifest_strings.txt', 'w', encoding='utf-8') as fh:
            for s in out:
                fh.write(repr(s) + '\n')
        print('--- STRINGS n=%d written to manifest_strings.txt ---' % n)
        sys.stdout.flush()
        break
    else:
        pos += size
