define reload
kill
monitor jtag_reset
load
end

target extended localhost:4242
load

set disassemble-next-line on
show disassemble-next-line on

layout asm
layout regs

break main

