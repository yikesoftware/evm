bin = open("./bin","wb")

p = b'''
    \x40\x00
    \x53\x02
    \x50\x00
    \x51\x00
    \x52\x0d
    \x80
    \x50\x01
    \x51\x00
    \x52\x0d
    \x80
    \x45
    \x24
    \x26
    \x49
    \x72\x04
    \x90'''
p = p.replace(b" ",b"")
p = p.replace(b"\x0a",b"")
print(len(p))
bin.write(p)