# CHIPPP-8, a CHIP-8 Emulator
A simple Chip-8 emulator written in C++, using the SDL library.

### Current progress:

| Instruction   | Done? |
|---------------|-------|
| SYS addr      | *1    |
| CLS           | X     |
| RET           | X     |
| JP addr       | X     |
| CALL addr     | X     |
| SE Vx, Byte   | X     |
| SNE Vx, Byte  | X     |
| SE Vx, Vy     | X     |
| LD Vx, Byte   | X     |
| ADD Vx, Byte  | X     |
| LD Vx, Vy     | X     |
| OR Vx, Vy     | X     |
| AND Vx, Vy    | X     |
| XOR Vx, Vy    | X     |
| ADD Vx, Vy    | X     |
| SUB Vx, Vy    | X     |
| SHR Vx {, Vy} | X     |
| SUBN Vx, Vy   | X     |
| SHL Vx {, Vy} | X     |
| SNE Vx, Vy    | X     |
| LD I, addr    | X     |
| JP V0, addr   |       |
| RND Vx, byte  |       |
| DRW Vx Vy nib |       |
| SKP Vx        |       |
| SKNP Vx       |       |
| LD Vx, DT     |       |
| LD Vx, K      |       |
| LD DT, Vx     |       |
| LD ST, Vx     |       |
| ADD I, Vx     |       |
| LD F, Vx      |       |
| LD B, Vx      |       |
| LD [I], Vx    |       |
| ADD Vx, [I]   |       |


*1 - originally used for old computers, not necessary for the interpreter

### Instructions to build and run:
TODO

### Notes:
Includes some public domain roms to test.
