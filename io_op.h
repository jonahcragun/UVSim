#ifndef IO_OP_H
#define IO_OP_H

#include <iostream>
#include <stdexcept>

// read word from terminal into specified memory index of main_memory
template <size_t SIZE>
void read(std::istream& is, short (&main_memory)[SIZE], short mem_addr) {
    if (mem_addr < 0 || mem_addr >= SIZE) {
        throw std::out_of_range("READ Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
    }
    is >> main_memory[mem_addr];
}

// write word from specified memory index to terminal
template <size_t SIZE>
void write(std::ostream& os, short (&main_memory)[SIZE], short mem_addr) {
    if (mem_addr < 0 || mem_addr >= SIZE) {
        throw std::out_of_range("WRITE Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
    }
    os << main_memory[mem_addr] << std::endl;
}

#endif
