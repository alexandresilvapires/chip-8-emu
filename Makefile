CC = g++
FLAGS = -Wall

.PHONY: all clean run

all: chip

clean:
	rm -f chip src/CHIPPP/.o

chip: src/CHIPPP/main.cpp src/CHIPPP/chip8.h src/CHIPPP/keyboard.h src/CHIPPP/memory.h src/CHIPPP/register.h src/CHIPPP/screen.h src/CHIPPP/sound.h src/CHIPPP/stack.h src/CHIPPP/system.h src/CHIPPP/timer.h
	$(CC) $(FLAGS) -o chip -c src/CHIPPP/main.cpp
