import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
data = open(r'E:\android_version\LIXCLIENT_version2\teamproxy\payload_modes\ALL01_1F_Assembly-CSharp-patch.bytes','rb').read()

def hexdump(off, ln=128):
    for i in range(off, min(off+ln, len(data)), 16):
        b = data[i:i+16]
        asc = ''.join(chr(c) if 32 <= c < 127 else '.' for c in b)
        print('0x%04x: %-48s %s' % (i, b.hex(' '), asc))

# The method code region = between the string records we identified:
# 'getBytes'(0x4e60) is a memberref in the method. The IL instructions (ldc/newarr/call)
# live BEFORE the member refs (they are operands AFTER opcodes). Let me look at what's
# immediately BEFORE the crypto string section (0x4d40-0x4e60) for the ldc.i4/newarr bytecode
print('=== pre-crypto IL region 0x4d40-0x4e60 ===')
hexdump(0x4d40, 0x120)
