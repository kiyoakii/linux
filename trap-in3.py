output = open('/dev/shm/inst', 'w')
nlines = 0

while True:
    gdb.execute("si")
    pc = gdb.selected_frame().pc()
    inst = gdb.execute('x/i $pc', to_string=True)
    output.write(inst)
    if pc == 0x401984:
        break
    nlines += 1
output.flush()
print(nlines)
