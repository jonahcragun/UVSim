#ifndef ARITHMETIC_OP_H
#define ARITHMETIC_OP_H

//Function declaration for arithmetic operations
void divide(int& accumulator, int* main_memory, int mem_addr);
void multiply(int& accumulator, int* main_memory, int mem_addr);
void add(int& accumulator, int* main_memory, int mem_addr);
void subtract(int& accumulator, int* main_memory, int mem_addr);

void checkOverflow(int& accumulator);
#endif
