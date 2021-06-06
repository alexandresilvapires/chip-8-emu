#ifndef __MEMORY_H_
#define __MEMORY_H__

#include "system.h"
#include "vector"

class Memory {

    private:
        std::vector<char> _memory; // Uses char since memory is byte-addressed, and this simplifies the process

    public:

        Memory(){
            _memory = std::vector<char>(MEMORY_SIZE);
        }


        Memory(int size){
            _memory = std::vector<char>(size);
        }

        void write(int i, char content){
            // We assure that the memory being accessed isn't out of bounds
            _memory[i % _memory.size()] = content;
        }

        char read(int i){
            // We assure that the memory being accessed isn't out of bounds
            return _memory[i % _memory.size()];
        }
};

#endif 