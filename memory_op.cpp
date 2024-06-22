#include "memory_op.h"
#include "constants.h"
#include <string>

#include <stdexcept>

// Load a word from a specific location in memory into the accumulator
void load(short& accumulator, short* main_memory, short mem_addr) {
if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("LOAD Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
    }
    accumulator = main_memory[mem_addr];
}

// Store a the value in the accumulator to a specific location in memory
void store(short& accumulator, short* main_memory, short mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("STORE Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
    }
    main_memory[mem_addr] = accumulator;
}
