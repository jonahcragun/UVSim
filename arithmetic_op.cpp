#include "arithmetic_op.h"
#include "constants.h"
#include <stdexcept>
#include <string>

// Function to check for overflow with six-digit
void checkOverflow(int& accumulator) {
    if (accumulator < MIN_VALUE || accumulator > MAX_VALUE) {
        accumulator %= 1000000; // Ensure the accumulator is within six digits
        if (accumulator < MIN_VALUE) {
            accumulator += 1000000; // Adjust if the value is still negative
        }
    }
}

// Divide the value in the memory to the accumulator
void divide(int& accumulator, int* main_memory, int mem_addr) {
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
void multiply(int& accumulator, int* main_memory, int mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("MULTIPLY Error: Memory address " + std::to_string(mem_addr) + " is out of range.\n");
    }
    accumulator *= main_memory[mem_addr];
    checkOverflow(accumulator);
}

// Add the value in the memory address to the accumulator
void add(int& accumulator, int* main_memory, int mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("ADD Error: Memory address " + std::to_string(mem_addr) + " is out of range.\n");
    }
    accumulator += main_memory[mem_addr];
    checkOverflow(accumulator);
}

// Subtract the value in the memory address from the accumulator
void subtract(int& accumulator, int* main_memory, int mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("SUBTRACT Error: Memory address " + std::to_string(mem_addr) + " is out of range.\n");
    }
    accumulator -= main_memory[mem_addr];
    checkOverflow(accumulator);
}
