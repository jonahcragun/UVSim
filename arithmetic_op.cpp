#include "arithmetic_op.h"
#include "constants.h"
#include <stdexcept>
#include <string>

// Function to check for overflow
void checkOverflow(short& accumulator) {
    accumulator = (accumulator < -9999 || accumulator > 9999) ? accumulator % 10000 : accumulator;
}

// Divide the value in the memory to the accumulator
void divide(short& accumulator, short* main_memory, short mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("DIVIDE Error: Memory address " + std::to_string(mem_addr) + " is out of range.\n");
    }
    if (main_memory[mem_addr] == 0) {
        throw std::runtime_error("DIVIDE Error: Division by zero.\n");
    }
    accumulator /= main_memory[mem_addr];
    checkOverflow(accumulator);
}

// Multiply the value in the memory to the accumulator
void multiply(short& accumulator, short* main_memory, short mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("MULTIPLY Error: Memory address " + std::to_string(mem_addr) + " is out of range.\n");
    }
    accumulator *= main_memory[mem_addr];
    checkOverflow(accumulator);
}

// Add the value in the memory address to the accumulator
void add(short& accumulator, short* main_memory, short mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("ADD Error: Memory address " + std::to_string(mem_addr) + " is out of range.\n");
    }
    accumulator += main_memory[mem_addr];
    checkOverflow(accumulator);
}

// Subtract the value in the memory address from the accumulator
void subtract(short& accumulator, short* main_memory, short mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("SUBTRACT Error: Memory address " + std::to_string(mem_addr) + " is out of range.\n");
    }
    accumulator -= main_memory[mem_addr];
    checkOverflow(accumulator);
}
