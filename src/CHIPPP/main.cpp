#include "keyboard.h"
#include "memory.h"
#include "register.h"
#include "screen.h"
#include "sound.h"
#include "stack.h"
#include "system.h"
#include "timer.h"

#include "iostream"
#include "fstream"

int main(int argc, char *argv[]){
    
    // Verify input

    if (argc != 1){
        std::cerr << "Invalid arguments given: ./chip romPath" << std::endl;
        return -1;
    }

    char* romPath = argv[0]; //Path to the rom that shall be played

    // System modules and variables

    int pc = 0x200;       // Program counter: Memory from 0x0 to 0x1FF are reserved, so we start at 0x200
    unsigned char sp = 0; // Stack pointer. TODO: current stack implementation doesnt care about sp!

    Memory mem = Memory();
    Register reg = Register();
    Sound sound = Sound();
    Timer timer = Timer();

    // Open the rom and loads it into memory
	std::fstream rom;
	rom.open(romPath, std::ios::in);

	if (!rom) {
		std::cerr << "Could not open rom!" << std::endl;
	}

    mem.loadRom(rom);
	


    // Close the rom
    rom.close();
}

// Fetches the instruction from memory
unsigned char fetch(Memory m, int pc){
    return m.read(pc);
}


