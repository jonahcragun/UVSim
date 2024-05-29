#include "memory_op.h"
#include <iostream>
#include <stdexcept>

// Load a word from a specific location in memory into the accumulator.
void load(short& accumulator, const short (&main_memory)[100], short mem_addr) {
    if (mem_addr >=0 && mem_addr < 100){
        accumulator = main_memory[mem_addr];
    }
    else{
        // Handle error: invalid address
        std::cerr << "Error: Invalid memory address for load operation." << std::endl;
        // For simplicity, let's just set the accumulator to 0
        accumulator = 0;
    }
}

// Store a the value in the accumulator to a
void store(short& accumulator, short (&main_memory)[100], short mem_addr) {
    if (mem_addr < 0 || mem_addr >= 100) {
        throw std::out_of_range("STORE Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
    }
    main_memory[mem_addr] = accumulator;
}