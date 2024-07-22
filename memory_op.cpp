#include "memory_op.h"
#include "constants.h"
#include <string>
#include <stdexcept>

// Load a word from a specific location in memory into the accumulator
void load(int& accumulator, int* main_memory, int mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("LOAD Error: Memory address " + std::to_string(mem_addr) + " is out of range.\n");
    }
    accumulator = main_memory[mem_addr];
}

// Store a the value in the accumulator to a specific location in memory
void store(int& accumulator, int* main_memory, int mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("STORE Error: Memory address " + std::to_string(mem_addr) + " is out of range.\n");
    }

    bool overwrite_warning = (abs(main_memory[mem_addr]) == 4300) ? true : false;

    main_memory[mem_addr] = accumulator;

    if (overwrite_warning) {
        throw std::logic_error("READ Warning: HALT code has been overwritten in memory address[" + std::to_string(mem_addr) + "].\n");
    }
}
