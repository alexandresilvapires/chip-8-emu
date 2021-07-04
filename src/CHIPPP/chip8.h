#ifndef __CHIP8_H__
#define __CHIP8_H__

#include "keyboard.h"
#include "memory.h"
#include "register.h"
#include "screen.h"
#include "sound.h"
#include "stack.h"
#include "system.h"
#include "timer.h"

#include "vector"
#include "iostream"

class Chip8 {

    private:
        // System modules and variables
        int pc = 0x200;       // Program counter: Memory from 0x0 to 0x1FF are reserved, so we start at 0x200
        unsigned char sp = 0; // Stack pointer. TODO: current stack implementation doesnt care about sp!


        Memory mem = Memory();
        Register reg = Register();
        Sound sound = Sound();
        Timer timer = Timer();
        Screen screen = Screen();
        Stack stack = Stack();

    public:
        Chip8(){}

        // Fetches the instruction from memory
        int fetch(){
            return mem.read(pc);
        }

        // Given an instruction, decodes it and executes it
        void decode(int instr) {

            switch(instr) {
                case 0x00E0:    // Clear screen instruction
                    screen.clearDisplay();
                    pc += 2;
                    break;

                case 0x00EE:    // Return from subroutine
                    pc = stack.pop();
                    break;

                default:
                    // We go here when the instruction is based on an opcode
                    // The next instructions are defined by their first 4 bits
                    int op = getNibble(instr, 0xF000, 12);

                    switch(op) {

                        case 1: //jump, format 1NNN where NNN is the address
                            pc = getNibble(instr, 0x0FFF, 0, 12);
                            break;

                        case 2: //Call, format 2NNN where NNN is the address to jump
                            stack.push(pc);
                            pc = getNibble(instr, 0x0FFF, 0, 12);
                            break;

                        case 3: //Skip next instruction if Vx == kk, format 3xkk
                            unsigned char x = (unsigned char) getNibble(instr, 0x0F00,8,12);
                            int kk = getNibble(instr, 0x00FF,0,8);

                            if(reg.read(x) == kk){
                                pc += 2;
                            }
                            pc += 2;
                            break;

                        case 4: //Skip next instruction if Vx != kk, format 3xkk
                            unsigned char x = (unsigned char) getNibble(instr, 0x0F00,8,12);
                            int kk = getNibble(instr, 0x00FF,0,8);
                            
                            if(reg.read(x) != kk){
                                pc += 2;
                            }
                            pc += 2;
                            break;

                        case 5: //Skip next instruction if Vx == Vy, format 3xy0
                            unsigned char x = (unsigned char) getNibble(instr, 0x0F00,8,12);
                            unsigned char y = (unsigned char) getNibble(instr, 0x00F0,4,8);
                            
                            if(reg.read(x) == reg.read(y)){
                                pc += 2;
                            }
                            pc += 2;
                            break;

                        case 6: //set reg VX to val NN, format 6XNN
                            int x = getNibble(instr, 0x0F00, 0, 12);
                            unsigned char nn = (unsigned char) getNibble(instr, 0x00FF, 0, 8);
                            reg.write(x, nn);
                            pc += 2;
                            break;

                        case 7: //add val NN to reg VX, format 7XNN
                            int x = getNibble(instr, 0x0F00, 0, 12);
                            unsigned char nn = (unsigned char) getNibble(instr, 0x00FF, 0, 8);
                            reg.write(x, reg.read(x) + nn);
                            pc += 2;
                            break;

                        case 8: //Used for operations between two registers, format 8xyN
                            unsigned char x = (unsigned char) getNibble(instr, 0x0F00, 8, 12);
                            unsigned char y = (unsigned char) getNibble(instr, 0x0F00, 4, 8);
                            int n = getNibble(instr, 0x0F00, 0, 4);

                            switch(n){
                                case 0: // Set Vx to Vy
                                    reg.write(x, reg.read(y));
                                    break;

                                case 1: // OR between x and y, result store in x
                                    unsigned char res = reg.read(x) | reg.read(y);
                                    reg.write(x, res);
                                    break;

                                case 2: // AND between x and y, result store in x
                                    unsigned char res = reg.read(x) & reg.read(y);
                                    reg.write(x, res);
                                    break;

                                case 3: // XOR between x and y, result store in x
                                    unsigned char res = reg.read(x) ^ reg.read(y);
                                    reg.write(x, res);
                                    break;

                                case 4: // ADD x and y, result store in x, carry flag in VF
                                    unsigned char res = reg.read(x) + reg.read(y);

                                    reg.write(15, (unsigned char) res > 255 ? 1 : 0);
                                    reg.write(x, res % 256);
                                    break;

                                case 5: // SUB x and y, result store in x, NOT borrow flag in VF
                                    unsigned char res = reg.read(x) - reg.read(y);

                                    reg.write(15, (unsigned char) res > 0 ? 1 : 0);
                                    reg.write(x, res);
                                    break;

                                case 6: // SHR x, 1 in VF if least significant bit in x is 1
                                    unsigned char vx = reg.read(x);

                                    reg.write(15, vx % 2);
                                    reg.write(x, vx >> 1);
                                    break;

                                case 7: // SUB y and x, result store in x, NOT borrow flag in VF
                                    unsigned char res = reg.read(y) - reg.read(x);

                                    reg.write(15, (unsigned char) res > 0 ? 1 : 0);
                                    reg.write(x, res);
                                    break;

                                case E: // SHL x, 1 in VF if most significant bit in x is 1
                                    unsigned char vx = reg.read(x);

                                    reg.write(15, vx << 7);
                                    reg.write(x, vx << 1);
                                    break;
                            }
                            
                            pc += 2;
                            break;

                        case 10: //set ireg to value NNN, format ANNN
                            int nnn = getNibble(instr, 0x0FFF, 0, 12);
                            reg.write_i(nnn);
                            pc += 2;
                            break;
                    }


            }
        }

        // Given an instruction, gets the bytes from the mask
        // Then shifts based on the byte interval in shiftLow/High to cut unnecessary bits
        // Eg: ABCD & 0FF0 -> 0BC0, shift interval (4,12) -> BC
        int getNibble(int instr, int mask = 0xFFFF, int shiftLow = 0, int shiftHigh = 16){
            return ((instr && mask) % pow(2,shiftHigh) >> shiftLow);
        }

};

#endif 