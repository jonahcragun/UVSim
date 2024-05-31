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
    unsigned short execute_op(short op_code, short mem_addr, unsigned short cur);
    void run();

public:
    UVSim();
};

#endif