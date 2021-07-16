#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "system.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class Memory {

    private:
        std::vector<unsigned char> _memory; // Uses char since memory is byte-addressed, and this simplifies the process

        unsigned char _fontset[80] =
            { 
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
            };

    public:

        Memory(){
            _memory = std::vector<unsigned char>(MEMORY_SIZE);

            loadFont();     //Loads the default font in memory
        }


        Memory(int size){
            _memory = std::vector<unsigned char>(size);
        }

        void write(int i, unsigned char content){
            // We assure that the memory being accessed isn't out of bounds
            _memory[i % _memory.size()] = content;
        }

        unsigned char read(int i){
            // We assure that the memory being accessed isn't out of bounds
            return _memory[i % _memory.size()];
        }

        int readInstruction(int i){
            // We assure that the memory being accessed isn't out of bounds, reads two consecutive places in memory
            return _memory[i % _memory.size()]*0x0100 + _memory[(i+1) % _memory.size()];
        }

        void loadRom(char* rom, int size){
            // Loads the rom byte by byte to the memory, in big endian fashion
            //TODO VERIFY ALL THIS

            for(int i = 0x200; i < size; i++){
                //std::cout << rom[i] << std::endl;
                write(i, rom[i]);
            }
        }

        void loadFont(){
            //Loads the default font into memory
            for(int i = 0; i < 80; i++){
                write(i, _fontset[i]);
            }
        }
};

#endif 