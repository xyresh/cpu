# cpu

basic af emulator for simple cpu


It is a 32 bit cpu  with 10 registers

r1 and r2 are operands A and B,
all others are general purpose.

included is a basic "assembler"
which doesn't do much however for now it can make the coding process for the cpu itself much easier.

the instruction set for now consists of:
instruction| description
-----------|-----------------
ADD  | add 2 intergers
SUB  | subtract 2 intergers
INC  | increment interger by one
DEC  | decrement interger by one
AND  | and
OR  | or
XOR  | xor

All above instructions must be written with the following syntax in order for the assembler to work.<br>
E.X.:
<br>

  `ADD 1 1 r4` -> add 1 and 2 and save the result to register 4
  
for the increment and decrement commands the second operand is irelevant, howver the third operand is important as it is the output register.<br>
E.X.:<br>
  `INC 1 0 r5` -> the 0 doesnt affect the command.
  


You can also find the PRT command.
For this phase of the cpu the PRT command is a simple print command which prints any register in memory.<br>
the syntax is:<br>
  `PRT 2` -> print contents of register 2, Note that you must only use the register number and not the "r2" format.

The CPU also features a Multi purpose Flag, which may be used to define function of a couple of instructions

For any arithmetic or logic operations the flag defines the following operations:
Flag  |  Description
------|--------------------------------
0x00  |  action between two Numbers
0x01  |  action between number and r2
0x02  |  action between both r1 and r2

There has also been an implementation of a MOV instruction:
Which takes advantage of the flags,
specifically:

Flag  |  Description
------|-----------------------------------
0x00  |  Move from register to register
0x01  |  Move Value to register
0x02  |  Move from register to memory
0x03  |  Move from memory to register


the emulator can run in interpreter mode by parsing `./cpu i` as your command line argument, or "run" mode, by `./cpu r <file name>`.
you can directly write machine code in hexadecimal instructions form.
an example would be:

Instruction in hex | Description
-------------------|-------------------------------------
100A0F05           | add 10 15 to r5
B0050000           | push r5 to stack
A0000000           | set program counter to 0 (jump to 0)
00000000           | program finish


instructions take the form of 32 bit instructions

op    | flag | opA  | opB  | Target
------|------|------|------|--------
4 bits|4 bits|8 bits|8 bits|8 bits
