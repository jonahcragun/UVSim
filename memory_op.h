#ifndef MEMORY_OP_H
#define MEMORY_OP_H

#include <iostream>
#include <stdexcept>

// Load a word from a specific location in memory of template size into the accumulator.
template <size_t SIZE>
void load(short& accumulator, const short (&main_memory)[SIZE], short mem_addr) {
    if (mem_addr < 0 || mem_addr >= SIZE) {
        throw std::out_of_range("LOAD Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
    }
    accumulator = main_memory[mem_addr];
}

// Template to store a the value in the accumulator to a specific location in memory of template size.
template <size_t SIZE>
void store(short& accumulator, short (&main_memory)[SIZE], short mem_addr) {
    if (mem_addr < 0 || mem_addr >= SIZE) {
        throw std::out_of_range("STORE Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
    }
    main_memory[mem_addr] = accumulator;
}

#endif