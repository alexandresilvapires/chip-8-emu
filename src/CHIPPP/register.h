#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <sstream>
#include <stdio.h>
#include <string.h>
#include "vector"
#include "iostream"

class Register {

    private:
        std::vector<unsigned char> _registers; // Uses char since memory is byte-addressed, and this simplifies the process

        int _iregister;              // Index register, used to point at memory locations

    public:

        Register(){
            _registers = std::vector<unsigned char>(16);

            _iregister = 0;
        }


        void write(int i,unsigned char content){
            // We assure that the memory being accessed isn't out of bounds
            _registers[i % _registers.size()] = content;
        }

        void write(const char *reg, char unsigned content){
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

        unsigned char read(int i){
            // We assure that the memory being accessed isn't out of bounds
            return _registers[i % _registers.size()];
        }

        unsigned char read(const char *reg){
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

        void write_i(int content){
            // Even though the index register is 16 bit, it can only point to the first 4096 bytes of memory (12 bits)
            // So accessing more than that is considered an invalid value
            if(content > 4096){
                std::cout << "FATAL: Invalid index register memory write requested." << std::endl;
            }
            _iregister = content;
        }

        int read_i(){
            return _iregister;
        }
};

#endif 