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

// Reset memory to 0
void UVSim::reset_memory() {
    for (short& mem_addr : main_memory) {
        mem_addr = 0;
    }
}

void UVSim::read_from_stream(std::istream& is, short* main_memory) {
    if (!is) {
        throw std::runtime_error("READ_FILE Error: Invalid file entered");
    }

    std::string line;
    unsigned short i = 0;

    while (std::getline(is, line)) {
        if (i > MEMORY_SIZE - 1)
            throw std::runtime_error("READ_FILE Error: File is too long: cannot exceed " + std::to_string(MEMORY_SIZE) + " lines");

        if (line.empty()) {
            continue;
        } else if (line.length() > 4) {
            if (line[0] == '-' || line[0] == '+')
                line = line.substr(0, 5); // Only keep the first 5 characters
            else
                line = line.substr(0, 4); // Only keep the first 4 characters
        }

        try {
            for (int j = 0; j < line.length(); ++j) {
                char c = line[j];
                if (j == 0 && (c == '-' || c == '+')) {
                    continue;
                }
                if (!isdigit(c)) {
                    throw std::runtime_error("READ_FILE Error: Invalid format '" + line + "' at line " + std::to_string(i));
                }
            }
            main_memory[i] = std::stoi(line);
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("READ_FILE Error: Invalid format '" + line + "' at line " + std::to_string(i));
        }

        ++i;
    }
}

// Read in file to memory starting at location 00
void UVSim::read_file() {
    std::string file;
    std::cout << "Enter a BasicML file name: ";
    std::cin >> file;

    std::ifstream ifs(file);

    // Check if file is valid
    if (!ifs) {
        throw std::runtime_error("READ_FILE Error: Invalid file entered");
    }

    // Check if file is empty
    if (ifs.peek() == std::ifstream::traits_type::eof()) {
        throw std::runtime_error("READ_FILE Error: File is empty");
    }

    read_from_stream(ifs, main_memory);

    ifs.close();
}

// Run program starting at memory location 00
void UVSim::execute() {
    unsigned short cur = 0;
    while (cur < MEMORY_SIZE && cur >= 0) {
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
    instr = abs(instr);
    *op_code = instr / 100;
    *mem_addr = instr % 100;
}

// Execute operation associated with op code
// Return next memory address to run
unsigned short UVSim::execute_op(short op_code, short mem_addr, short cur) {
    // 10: READ
    if (op_code == 10) {
        while (true) {
            try {
                std::cout << "Enter a number: ";
                read(std::cin, main_memory, mem_addr);
                break;
            } catch (const std::exception &e) {
                std::cout << e.what() << "' please enter an integer." << std::endl;
            }
        }
    }
        // 11: WRITE
    else if (op_code == 11) {
        write(std::cout, main_memory, mem_addr);
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
        throw std::runtime_error("EXECUTE_OP Warning | Line " + std::to_string(cur) + ": Unexpected value '" + std::to_string(op_code) + std::to_string(mem_addr) + "' in instruction memory.");
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
        throw std::out_of_range("SET_MEMORY_VALUE Error: Memory address " + std::to_string(mem_addr) + " is out of range.");
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