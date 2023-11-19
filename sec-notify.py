output = open('/dev/shm/inst-seccomp-notify', 'w')
nlines = 0

while True:
    gdb.execute("si")
    pc = gdb.selected_frame().pc()
    try:
        inst = gdb.execute('x/i $pc', to_string=True)
    except:
        # output.write("gdb interpreting err")
        pass
    # output.write(inst)
    if pc == 0x401ef2:
        output.write(f"breakpoint: the tracee is trying to make a syscall, nlines={nlines}")
    elif pc == 0x401f0f:
        output.write(f"breakpoint: the syscall is finished, tracee continues, nlines={nlines}")
        break
    elif pc == 0x4020ea:
        output.write(f"breakpoint: the tracer gets notified, nlines={nlines}")
    nlines += 1
output.flush()
print(nlines)
