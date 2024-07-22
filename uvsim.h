#ifndef UVSIM_H
#define UVSIM_H

#include "constants.h"
#include "input_handler.h"
#include "output_handler.h"
#include <vector>
#include <string>

// UVSim VM that interprets BasicML (a simple machine language)
// has a memory array and accumulator register
class UVSim {
private:
    int main_memory[MEMORY_SIZE];
    int accumulator;

    InputHandler* input_handler;
    OutputHandler* output_handler;

    void reset_memory();
    void execute();
    void split_instr(int instr, int* op_code, int* mem_addr);
    void parse_input(std::vector<std::string>& lines);

public:
    unsigned int execute_op(int op_code, int mem_addr, unsigned int cur);
    int& get_accumulator();
    int* get_memory();
    int get_memory_value(int mem_addr);

    void set_accumulator(int value);
    void set_memory_address(int mem_addr, int value);
    void run();

    UVSim(InputHandler* handler_in, OutputHandler* handler_out);
};

#endif
