import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
for fn in ['libXZAXZAXZAXZA.so.enc', 'libZZZZZZZZZZZZ.so.enc', 'libQWERTYUIOPAS.so.enc']:
    d = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\\' + fn, 'rb').read()
    print('=== %s (size %d) ===' % (fn, len(d)))
    print('  first 0x30:', d[:0x30].hex(' '))
    asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in d[:0x30])
    print('  ascii     :', asc)
    # look for a length/magic field: interpret first 4 bytes BE/LE
    import struct
    for fmt, nm in [('<I','u32le'), ('>I','u32be'), ('<Q','u64le'), ('>Q','u64be')]:
        v = struct.unpack_from(fmt, d, 0)[0]
        print('  %s @0: %d (0x%x)' % (nm, v, v))
print()
print('XZ vs QW first 0x28 identical?', open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libXZAXZAXZAXZA.so.enc','rb').read()[:0x28] == open(r'E:\android_version\LIXCLIENT_version2\teamproxy\libQWERTYUIOPAS.so.enc','rb').read()[:0x28])
