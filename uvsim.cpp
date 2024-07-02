#include "uvsim.h"
#include "constants.h"
#include "io_op.h"
#include "memory_op.h"
#include "arithmetic_op.h"
#include "control_op.h"

#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>

// Reset memory to 0
void UVSim::reset_memory() {
    accumulator = 0;
    for (short& mem_addr : main_memory) {
        mem_addr = 0;
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

// Put instructions into memory. Only accept 4 digits and sign.
// Param 1: Vector of full lines from the file
void UVSim::parse_input(std::vector<std::string>& lines){
    if (lines.size() > 100) {
        *output_handler << "INSTRUCTIONS SIZE Error: Passed instructions are too long at count of '"
                        << lines.size() << "'. Cannot exceed " << std::to_string(MEMORY_SIZE)
                        << " instructions." << std::endl;
        output_handler->handle_output();
    }

    size_t i = 0;
    for (auto line : lines) {
        try {
            input_handler->validate_instruction(line);
            main_memory[i] = std::stoi(line);
        } 
        catch (const std::invalid_argument& e) {
            *output_handler << "INSTRUCTION Error | memory address [" << std::setw(2) << std::setfill('0')
                            << i << "]: " << e.what() << std::endl;
            output_handler->handle_output();
        }
        i++;
    }
}

// Run program starting at memory location 00
void UVSim::execute() {
    short op_code;
    short mem_addr;

    for (unsigned short current_memory_address = 0; current_memory_address < MEMORY_SIZE;
         current_memory_address = execute_op(op_code, mem_addr, current_memory_address)) {

        split_instr(main_memory[current_memory_address], &op_code, &mem_addr);
    }
}

// Execute operation associated with op code
// Return next memory address to run
unsigned short UVSim::execute_op(short op_code, short mem_addr, unsigned short cur_mem_addr) {
    try{
        bool can_exit = false;

        switch (op_code) {
        case 10: // 10: READ
            while (!can_exit) {
                try {
                    read(input_handler->get_user_input(), main_memory, mem_addr);
                    can_exit = true;
                } catch (const std::invalid_argument& logic_err){
                    *output_handler << logic_err.what();
                    output_handler->handle_output();
                } catch (const std::logic_error &e) {
                    *output_handler << e.what();
                    output_handler->handle_output();
                    can_exit = true;
                } catch (const std::exception &e) {
                    *output_handler << e.what();
                    output_handler->handle_output();
                }
            }
            break;
        case 11: // 11: WRITE
            *output_handler << "Output: ";
            write(*output_handler, main_memory, mem_addr);
            output_handler->handle_output();
            break;
        case 20: // 20: LOAD
            load(accumulator, main_memory, mem_addr);
            break;
        case 21: // 21: STORE
            store(accumulator, main_memory, mem_addr);
            break;
        case 30: // 30: ADD
            add(accumulator, main_memory, mem_addr);
            break;
        case 31: // 31: SUBTRACT
            subtract(accumulator, main_memory, mem_addr);
            break;
        case 32: // 32: DIVIDE
            divide(accumulator, main_memory, mem_addr);
            break;
        case 33: // 33: MULTIPLY
            multiply(accumulator, main_memory, mem_addr);
            break;
        case 40: // 40: BRANCH
            return branch(mem_addr);
        case 41: // 41: BRANCHNEG
            return branchNeg(accumulator, cur_mem_addr, mem_addr);
        case 42: // 42: BRANCHZERO
            return branchZero(accumulator, cur_mem_addr, mem_addr);
        case 43: // 43: HALT
            return halt();
        default: // INVALID OPCODE
            *output_handler << "EXECUTE_OP Warning |  memory address [" << std::setw(2) << std::setfill('0')
                            << cur_mem_addr << "]: " ": Encountered ";
            if (op_code == 0 && mem_addr == 0){
                *output_handler << "NULL value '"
                                << std::setw(2) << std::setfill('0') << op_code
                                << std::setw(2) << std::setfill('0') << mem_addr
                                << "'." << std::endl;
            } else {
            *output_handler << "UNEXPECTED value '"
                            << std::setw(2) << std::setfill('0') << op_code
                            << std::setw(2) << std::setfill('0') << mem_addr
                            << "' in instruction memory block." << std::endl;
            }
            *output_handler << "Skipping line..." << std::endl;
            output_handler->handle_output();
            break;
        }
    } catch (const std::logic_error& logic_err){
        *output_handler << logic_err.what() << std::endl;
        output_handler->handle_output();
    }
    return ++cur_mem_addr;
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
        throw std::out_of_range("GET_MEMORY_VALUE Error: Memory address " + std::to_string(mem_addr)
        + " is out of range.\n");
    }
    return main_memory[mem_addr];
}

// Set memory at a specific location
void UVSim::set_memory_address(short mem_addr, short value) {
    if (mem_addr < 0 || mem_addr >= MEMORY_SIZE) {
        throw std::out_of_range("SET_MEMORY_VALUE Error: Memory address " + std::to_string(mem_addr)
        + " is out of range.\n");
    }
    main_memory[mem_addr] = value;
}


// Set accumulator to a specific value
void UVSim::set_accumulator(short value) {
    accumulator = value;
}

// Start VM, loads passed vector<string> into memory, and executes the program
void UVSim::run() {
    std::vector<std::string> instr_lines = input_handler->get_instructions();
    if (instr_lines.empty()){
        throw std::runtime_error("UVSim Execution Error: Something went wrong when attempting to get UVSim instructions.\n");
    }
    parse_input(instr_lines);
    execute();
    reset_memory();
}

// Constructor, resets memory and accumulator on creation
UVSim::UVSim(InputHandler* handler_in, OutputHandler* hanlder_out) : input_handler(handler_in), output_handler(hanlder_out) {
    reset_memory();
}
