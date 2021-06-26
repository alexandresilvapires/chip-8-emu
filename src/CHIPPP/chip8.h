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

                default:
                    // We go here when the instruction is based on an opcode
                    // The next instructions are defined by their first 4 bits
                    int op = getNibble(instr, 0xF000, 12);

                    switch(op) {

                        case 1: //jump, format 1NNN where NNN is the address
                            pc = getNibble(instr, 0x0FFF, 0, 12);
                            break;

                        case 6: //set reg VX to val NN, format 6XNN
                            int x = getNibble(instr, 0x0F00, 0, 12);
                            unsigned char nn = getNibble(instr, 0x00FF, 0, 8);
                            reg.write(x, nn);
                            pc += 2;
                            break;

                        case 7: //add val NN to reg VX, format 7XNN
                            int x = getNibble(instr, 0x0F00, 0, 12);
                            unsigned char nn = getNibble(instr, 0x00FF, 0, 8);
                            reg.write(x, reg.read(x) + nn);
                            pc += 2;
                            break;

                        case 10: //set ireg to value NNNN, format ANNN
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