#include "chip8.h"
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

    // Open the rom and loads it into memory

    char* romPath = argv[0]; //Path to the rom that shall be played

	std::fstream rom;
	rom.open(romPath, std::ios::in);

	if (!rom) {
		std::cerr << "Could not open rom!" << std::endl;
        return -1;
	}
    

    Chip8 chip = Chip8(rom);
	
    //while true, emulate cycle (fetch, decode, execute), draw graphics and set pressed keys
    chip.run();

    // Close the rom
    rom.close();
}



