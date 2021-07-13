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

#include <vector>
#include <iostream>
#include <cstdlib>

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
        Keyboard keyboard = Keyboard();

    public:
        Chip8(){}

        Chip8(std::fstream& rom){
            mem.loadRom(rom);
        }

        void run(){
            while( decode( fetch() ));
        }

        // Fetches the instruction from memory
        int fetch(){
            return mem.read(pc);
        }

        // Given an instruction, decodes it and executes it- Returns true when screen is closed.
        bool decode(int instr) {

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

                                case 14: // SHL x, 1 in VF if most significant bit in x is 1
                                    unsigned char vx = reg.read(x);

                                    reg.write(15, vx << 7);
                                    reg.write(x, vx << 1);
                                    break;

                                default:
                                    break;
                            }
                            
                            pc += 2;
                            break;

                        case 9: //Skip next instruction if Vx != Vy, format 9xy0
                            unsigned char x = (unsigned char) getNibble(instr, 0x0F00,8,12);
                            unsigned char y = (unsigned char) getNibble(instr, 0x00F0,4,8);
                            
                            if(reg.read(x) != reg.read(y)){
                                pc += 2;
                            }
                            pc += 2;
                            break;

                        case 10: //set ireg to value NNN, format ANNN
                            int nnn = getNibble(instr, 0x0FFF, 0, 12);
                            reg.write_i(nnn);
                            pc += 2;
                            break;

                        case 11: //jump to NNN+V0, format BNNN where NNN is the address
                            pc = getNibble(instr, 0x0FFF, 0, 12) + reg.read(0);
                            break;

                        case 12: //Given a Vx, and a value kk, Vx = random byte AND kk. Format CXKK
                            unsigned char r = (unsigned char) rand() % 256;
                            unsigned char k = (unsigned char) getNibble(instr, 0x00FF,0,8);
                            
                            reg.write(getNibble(instr, 0x0F00, 8,12), r & k);

                            pc += 2;
                            break;

                        case 13: // Display a n pixels tall sprite starting at memory addr stored in I, in coords (Vx, Vy)
                                 // If any pixel is erased after being XORed, Vx is set to 1, else is set to 0. 
                                 // Pixels wrap around the screen if coordenates are outside the expected size
                                 // Format Dxyn

                            unsigned char n = (unsigned char) getNibble(instr, 0x000F,0,4);
                            unsigned char vx = reg.read( getNibble(instr, 0x0F00,8,12));
                            unsigned char vy = reg.read( getNibble(instr, 0x00F0,4,8));
                            int i = reg.read_i();

                            reg.write(15, 0); //reset VF

                            bool collision = false;

                            for(int k = 0; k < n; k++){

                                //Stores a row of pixels to draw 
                                unsigned char bitmap = mem.read(i);

                                //Cycle every bit of the bitmap
                                for(int l = 7; l >= 0; l--){
                                    unsigned char newbit = getNibble(bitmap, pow(2, l), l, 8);

                                    if(newbit == 1){
                                        collision = collision | screen.flipPixel(vx, vy);
                                    }

                                    vx++;

                                    //If we reach the right end of the screen, we break
                                    if(vx % WINDOW_INTERNAL_WIDTH == 0) break;
                                }

                                vy++;
                                    
                                 //If we reach the bottom end of the screen, we break
                                if(vy % WINDOW_INTERNAL_HEIGHT == 0) break;
                                i++;

                            }

                            if(collision) reg.write(15, 1);

                            pc += 2;
                            break;

                        case 14: // Used for keyboard instructions
                            
                            int n = getNibble(instr, 0x000F, 0, 4);

                            switch(n){
                                case 1: //Skip if key with the value Vx is not pressed, format EXA1
                                    unsigned char vx = reg.read( getNibble(instr, 0x0F00, 8, 12));
                                    
                                    if(keyboard.getKey((int) vx)) pc += 2;

                                    break;
                                
                                case 14: //Skip if key with the value Vx is pressed, format EX9E
                                    unsigned char vx = reg.read( getNibble(instr, 0x0F00, 8, 12));
                                    
                                    if(!keyboard.getKey((int) vx)) pc += 2;

                                    break;

                                default:
                                    break;
                                
                                pc += 2;
                                break;
                            }

                        case 15: // Used for load and add instructions over registers and items, usual format FX**
                            
                            int n = getNibble(instr, 0x00FF, 0, 8);
                            int x = getNibble(instr, 0x0F00, 8, 12);

                            switch(n){
                                case 7: //Set Vx to delay timer, format FX07
                                    
                                    reg.write(x, timer.getTimer());

                                    break;
                                
                                case 10: // Wait for a key press and store pressed key in Vx, format FX0A
                                    
                                    unsigned char key = keyboard.registerKeyboard();

                                    if(key == -1) return false;

                                    reg.write(x, key);

                                    break;

                                case 21: //Set delay timer to Vx, format FX15
                                    
                                    timer.setTimer( reg.read(x));

                                    break;
                                
                                case 24: //Set sound timer to Vx, format FX18
                                    
                                    sound.setTimer( reg.read(x));

                                    break;

                                case 30: //Set I = I + Vx, format FX1E
                                    
                                    reg.write_i( (int) reg.read(x) + reg.read_i());

                                    break;

                                case 41: //Set I = location of sprite for digit Vx using the known font. Format FX29
                                    
                                    // TODO verify this
                                    reg.write_i( 0x5 * reg.read(x));

                                    break;

                                case 51: // Store BCD representation of Vx in I, I+1 and I+2 (100s, 10s, 1s respectively).
                                        // Format FX33

                                    // TODO verify this

                                    unsigned char vx = reg.read(x);
                                    unsigned char units = vx % 10;
                                    unsigned char tens = vx % 100 - units;

                                    mem.write(reg.read_i() + 2, units);
                                    mem.write(reg.read_i() + 1, tens);
                                    mem.write(reg.read_i(), vx - tens);

                                case 85: // Stores registers 0 to Vx into I to I+X. Format FX55

                                    for(int i = 0; i <= x; i++){
                                        mem.write(reg.read_i() + i, (int) reg.read(i));
                                    }

                                case 101: // Write into registers 0 to Vx from addresses I to I+X. Format FX65

                                    for(int i = 0; i <= x; i++){
                                        reg.write(i ,mem.read(reg.read_i() + i));
                                    }

                                default:
                                    break;
                                
                                pc += 2;
                                break;
                            }


                        default: //Ignore unrecognized instructions
                            break;
                        return true;
                    }


            }
        }

        // Given an instruction, gets the bytes from the mask
        // Then shifts based on the byte interval in shiftLow/High to cut unnecessary bits
        // Eg: ABCD & 0FF0 -> 0BC0, shift interval (4,12) -> BC
        int getNibble(int instr, int mask = 0xFFFF, int shiftLow = 0, int shiftHigh = 16){
            return ((instr && mask) % (int) pow(2,shiftHigh) >> shiftLow);
        }

};

#endif 