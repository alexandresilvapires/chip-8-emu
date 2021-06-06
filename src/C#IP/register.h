#ifndef __REGISTER_H_
#define __REGISTER_H__

#include <sstream>
#include <stdio.h>
#include <string.h>
#include "vector"
#include "iostream"

class Register {

    private:
        std::vector<char> _registers; // Uses char since memory is byte-addressed, and this simplifies the process

    public:

        Register(){
            _registers = std::vector<char>(16);
        }


        void write(int i, char content){
            // We assure that the memory being accessed isn't out of bounds
            _registers[i % _registers.size()] = content;
        }

        void write(const char *reg, char content){
            // Registers are named from V0-VF, this uses a cheap method to get the register name
            if(strlen(reg) == 2 && reg[0] == 'V'){

                int i = std::stoul(&reg[1], nullptr, 16);

                // We assure that the memory being accessed isn't out of bounds
                _registers[i % _registers.size()] = content;
            }
            else{
                std::cout << "FATAL: Invalid register memory write requested." << std::endl;
            }
        }

        char read(int i){
            // We assure that the memory being accessed isn't out of bounds
            return _registers[i % _registers.size()];
        }

        char read(const char *reg){
            // Registers are named from V0-VF, this uses a cheap method to get the register name
            if(strlen(reg) == 2 && reg[0] == 'V'){

                int i = std::stoul(&reg[1], nullptr, 16);

                // We assure that the memory being accessed isn't out of bounds
                return _registers[i % _registers.size()];
            }
            else{
                std::cout << "FATAL: Invalid register memory write requested." << std::endl;
            }
        }
};

#endif 