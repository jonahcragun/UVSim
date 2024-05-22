#include "io_op.h"
#include <iostream>

// read word from terminal into specified memory index of main_memory
void read(short& accumulator, short (&main_memory)[100], short mi) {
	std::cin >> main_memory[mi];
}

// write word from specified memory index to terminal
void write(short& accumulator, short (&main_memory)[100], short mi) {
	std::cout << main_memory[mi];
}
