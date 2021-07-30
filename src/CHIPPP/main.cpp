#include "chip8.h"
#include "system.h"
#include "timer.h"

#include "iostream"
#include "fstream"

int main(int argc, char *argv[]){
    
    // Verify input
    
    if (argc != 2){
        std::cerr << "Invalid arguments given: ./chip romPath" << std::endl;
        return -1;
    }

    // Open the rom and loads it into memory

    char* romPath = argv[1]; //Path to the rom that shall be played

	std::ifstream file(romPath, std::ios::binary | std::ios::ate);


	if (!file.is_open()) {
		std::cerr << "Could not open rom!" << std::endl;
        return -1;
	}
    std::streampos size = file.tellg();
    unsigned char* rom = new unsigned char[size];
	file.seekg(0, std::ios::beg);
	file.read( (char*) rom, size);
	file.close();

    Chip8 chip = Chip8(rom, size);

    delete[] rom;
	
    //while true, emulate cycle (fetch, decode, execute), draw graphics and set pressed keys
    chip.run();

    return 0;
}



