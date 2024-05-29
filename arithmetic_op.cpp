#include "arithmetic_op.h"
#include <iostream>

void divide(short&, short*, short){

}

void multiply(short&, short*, short){

}

// Add the value in the memory address to the accumulator
void add(short& accumulator, short* main_memory, short& mem_addr) {
    if (mem_addr < 0 || mem_addr >= 100) {
        throw std::out_of_range("STORE Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
    }
    accumulator += main_memory[mem_addr];
}

// Subtract the value in the memory address from the accumulator
void subtract(short& accumulator, short* main_memory, short& mem_addr) {
    if (mem_addr < 0 || mem_addr >= 100) {
        throw std::out_of_range("STORE Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
    }
    accumulator -= main_memory[mem_addr];
}
