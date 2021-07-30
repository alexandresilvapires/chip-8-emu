# CHIPPP-8, a CHIP-8 Emulator
A simple Chip-8 emulator written in C++, using the SDL2 library.

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
| JP V0, addr   | X     |
| RND Vx, byte  | X     |
| DRW Vx Vy nib | X     |
| SKP Vx        | X     |
| SKNP Vx       | X     |
| LD Vx, DT     | X     |
| LD Vx, K      | X     |
| LD DT, Vx     | X     |
| LD ST, Vx     | X     |
| ADD I, Vx     | X     |
| LD F, Vx      | X     |
| LD B, Vx      | X     |
| LD [I], Vx    | X     |
| ADD Vx, [I]   | X     |

All instructions are implemented, yet some bugs still remain.

*1 - originally used for old computers, not necessary for a modern interpreter

### Instructions to build and run:

In order to build the emulator, the SDL2 library needs to be installed.
Instructions to do so can be found here: https://www.libsdl.org/download-2.0.php

Clone the repo, extract it, and in the terminal, cd to it. (Eg:'cd chip-8-emu')
Enter 'make' in the console, and run with './chip romPath'
Eg: ./chip roms/TICTAC

### Notes:
Includes some public domain roms to test.
