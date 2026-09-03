import io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
keys = ['ddb75c', 'd88e92', '575d26', '7a8410']
ciph = [0x18, 0x18, 0x49]
for k, c in zip(keys[:3], ciph):
    ch = c ^ ord(k[0])
    print(hex(c), 'xor', repr(k[0]), hex(ord(k[0])), '->', hex(ch), repr(chr(ch)))
