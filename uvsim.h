#ifndef UVSIM_H
#define UVSIM_H

#include "constants.h"

// UVSim VM that interprets BasicML (a simple machine language)
// has a memory array and accumulator register
class UVSim {
private:
    short main_memory[MEMORY_SIZE];
    short accumulator;

    void reset_memory();
    void read_file();
    void execute();
    void split_instr(short instr, short* op_code, short* mem_addr);

public:
    unsigned short execute_op(short op_code, short mem_addr, short cur);
    short& get_accumulator();
    short* get_memory();
    short get_memory_value(short mem_addr);
    void set_accumulator(short value);
    void set_memory_address(short mem_addr, short value);
    void run();

    UVSim();
};

#endif