#ifndef __MEMORY_H_
#define __MEMORY_H__

#include "system.h"
#include <vector>
#include <fstream>
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

        void write(int i, char content){
            // We assure that the memory being accessed isn't out of bounds
            _memory[i % _memory.size()] = content;
        }

        char read(int i){
            // We assure that the memory being accessed isn't out of bounds
            return _memory[i % _memory.size()];
        }

        void loadRom(std::fstream& rom){
            // Loads the rom byte by byte to the memory, in big endian fashion
            //TODO VERIFY ALL THIS

            std::string content;
            rom >> std::hex >> content;

            for(int i = 0x200; i < content.length(); i++){
                write(i, content[i]);
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