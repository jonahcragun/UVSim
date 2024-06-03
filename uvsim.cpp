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
    *mem_addr = instr % 100;
}

// Execute operation associated with op code
// Return next memory address to run
unsigned short UVSim::execute_op(short op_code, short mem_addr, short cur) {
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
        return halt();
    }
        // INVALID OPCODE
    else {
        string e = "Invalid op code at address: " + to_string(cur);
        throw runtime_error(e);
    }
    return ++cur;
}

// Get accumulator value
short& UVSim::get_accumulator() {
    return accumulator;
}

// Get memory array
short* UVSim::get_memory() {
    return main_memory;
}

// Get memory value at a specific location
short UVSim::get_memory_value(short mem_addr) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("GET_MEMORY_VALUE Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
    }
    return main_memory[mem_addr];
}

// Set memory at a specific location
void UVSim::set_memory_address(short mem_addr, short value) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw runtime_error("Memory address out of bounds");
    }
    main_memory[mem_addr] = value;
}


// Set accumulator to a specific value
void UVSim::set_accumulator(short value) {
    accumulator = value;
}

// Start VM, get user input for file name, load into memory, and execute program
void UVSim::run() {
    read_file();
    execute();
}

// Constructor, runs UVSim on creation
UVSim::UVSim() {
    reset_memory();
}
