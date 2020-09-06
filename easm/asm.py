bin = open("./bin","wb")

p = b'''
    \x40\x00
    \x46
    \x40\x00
    \x47
    \x40\x0d
    \x48
    \x80
    \x40\x01
    \x46
    \x40\x00
    \x47
    \x40\x0d
    \x48
    \x80
    \x90'''
p = p.replace(b" ",b"")
p = p.replace(b"\x0a",b"")
print(len(p))
bin.write(p)