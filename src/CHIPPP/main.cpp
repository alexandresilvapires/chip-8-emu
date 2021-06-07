#include "keyboard.h"
#include "memory.h"
#include "register.h"
#include "screen.h"
#include "sound.h"
#include "stack.h"
#include "system.h"
#include "timer.h"

int main(int argc, char *argv[]){
    
    // Verify input

    if (argc != 1){
        std::cerr << "Invalid arguments given: ./chip romPath" << std::endl;
        return -1;
    }

    char* romPath = argv[0]; //Path to the rom that shall be played

    // System modules and variables

    int pc = 0x200; // Program counter: Memory from 0x0 to 0x1FF are reserved, so we start at 0x200

    Memory mem = Memory();
    Register reg = Register();
}