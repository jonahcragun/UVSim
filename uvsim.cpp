#include "uvsim.h"
#include "constants.h"
#include "io_op.h"
#include "memory_op.h"
#include "arithmetic_op.h"
#include "control_op.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using std::cin;
using std::cout;
using std::ifstream;
using std::runtime_error;
using std::string;
using std::to_string;

// Reset memory to 0
void UVSim::reset_memory() {
    for (short& mem_addr : main_memory) {
        mem_addr = 0;
    }
}

// Read in file to memory starting at location 00
void UVSim::read_file() {
    string file;
    cout << "Enter a BasicML file name: ";
    cin >> file;

    ifstream ifs(file);

    // check if file is valid
    if (!ifs) {
        throw runtime_error("Invalid file entered");
    }

    string word;
    unsigned short i = 0;

    while (getline(ifs, word)) {
        if (i > MEMORY_SIZE - 1)
            throw runtime_error("File is too long: cannot exceed " + std::to_string(MEMORY_SIZE) + " lines");

        main_memory[i] = stoi(word);
        ++i;
    }
}

// Run program starting at memory location 00
void UVSim::execute() {
    unsigned short cur = 0;
    while (cur < MEMORY_SIZE) {
        short op_code;
        short mem_addr;

        split_instr(main_memory[cur], &op_code, &mem_addr);
        cur = execute_op(op_code, mem_addr, cur);
    }
}

// Separate instruction into 2 parts, operation code and memory address
// Param 1: instruction
// Param 2: pointer to op code value
// Param 3: pointer to mem addr value
void UVSim::split_instr(short instr, short* op_code, short* mem_addr) {
    *op_code = instr / 100;
    *mem_addr = instr - (*op_code * 100);
}

// Execute operation associated with op code
// Return next memory address to run
unsigned short UVSim::execute_op(short op_code, short mem_addr, unsigned short cur) {
    // 10: READ
    if (op_code == 10) {
        read(accumulator, main_memory, mem_addr);
    }
        // 11: WRITE
    else if (op_code == 11) {
        write(accumulator, main_memory, mem_addr);
    }
        // 20: LOAD
    else if (op_code == 20) {
        load(accumulator, main_memory, mem_addr);
    }
        // 21: STORE
    else if (op_code == 21) {
        store(accumulator, main_memory, mem_addr);
    }
        // 30: ADD
    else if (op_code == 30) {
        add(accumulator, main_memory, mem_addr);
    }
        // 31: SUBTRACT
    else if (op_code == 31) {
        subtract(accumulator, main_memory, mem_addr);
    }
        // 32: DIVIDE
    else if (op_code == 32) {
        divide(accumulator, main_memory, mem_addr);
    }
        // 33: MULTIPLY
    else if (op_code == 33) {
        multiply(accumulator, main_memory, mem_addr);
    }
        // 40: BRANCH
    else if (op_code == 40) {
        return branch(mem_addr);
    }
        // 41: BRANCHNEG
    else if (op_code == 41) {
        return branchNeg(accumulator, cur, mem_addr);
    }
        // 42: BRANCHZERO
    else if (op_code == 42) {
        return branchZero(accumulator, cur, mem_addr);
    }
        // 43: HALT
    else if (op_code == 43) {
        cur = halt();
    }
        // INVALID OPCODE
    else {
        string e = "Invalid op code at address: " + to_string(cur);
        throw runtime_error(e);
    }
    return ++cur;
}

// Start VM, get user input for file name, load into memory, and execute program
void UVSim::run() {
    reset_memory();
    read_file();
    execute();
}

// Constructor, runs UVSim on creation
UVSim::UVSim() {
    run();
}
