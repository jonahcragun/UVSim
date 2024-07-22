#ifndef IO_OP_H
#define IO_OP_H

#include "output_handler.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

// read word into specified memory index of main_memory
template <size_t SIZE>
void read(std::istream& is, int (&main_memory)[SIZE], int mem_addr) {
    std::ostringstream throw_context;
    if (mem_addr < 0 || static_cast<size_t>(mem_addr) >= SIZE) {
        throw std::out_of_range("READ Error: Memory address [" + std::to_string(mem_addr) + "] is out of range.\n");
    }

    std::string input;
    is >> input;

    if (input.empty()){
        throw std::runtime_error("Read warning: No input was provided.");
    }
    std::string original_input = input;
    size_t instruction_length = input.length();

    if (instruction_length == 1){
        char c = input[0];
        if (!isdigit(c)) {
            throw std::invalid_argument(
                    "READ Error: Invalid format '" + input + "'. Must be a sequence of 4 digits.");
        }
    }

    bool overwrite_warning = (abs(main_memory[mem_addr]) == 4300) ? true : false;
    bool size_warning = false;
    if (instruction_length > 6) {
        if (input[0] == '-' || input[0] == '+') {
            // Only keep the first 5 characters
            size_warning = (instruction_length > 7) ? true : false;
            input = input.substr(0, 7);
        } else {
            // Only keep the first 4 characters
            size_warning = (instruction_length > 6) ? true : false;
            input = input.substr(0, 6);
        }
    }

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (i == 0 && (c == '-' || c == '+')) {
            continue;
        }
        if (!isdigit(c)) {
            throw_context << "READ Error: Invalid format encountered '" << input << "'. Must be a sequence of 6 digits." << std::endl;
            throw std::invalid_argument(throw_context.str());
        }
    }
    main_memory[mem_addr] = std::stoi(input);
    if (size_warning || overwrite_warning) {
        if (size_warning) {
            throw_context << "READ Warning: Input character count too large. Only the first 6 signed digits sequence: '"
                          << input << "' from '" << original_input << "' will attempt to be stored.\n";
        }
        if (overwrite_warning) {
            throw_context << "READ Warning: HALT code has been overwritten in memory address["
                          << std::setw(2) << std::setfill('0') << mem_addr << "]." << std::endl;
        }
        throw std::logic_error(throw_context.str());
    }
}

// write word from specified memory index to terminal
template <size_t SIZE>
void write(std::ostream& os, int (&main_memory)[SIZE], int mem_addr) {
    if (mem_addr < 0 || static_cast<size_t>(mem_addr) >= SIZE) {
        throw std::out_of_range("WRITE Error: Memory address [" + std::to_string(mem_addr) + "] is out of range.\n");
    }
    os << main_memory[mem_addr] << std::endl;
}

template <size_t SIZE>
void write(OutputHandler& os, int (&main_memory)[SIZE], int mem_addr) {
    if (mem_addr < 0 || static_cast<size_t>(mem_addr) >= SIZE) {
        throw std::out_of_range("WRITE Error: Memory address [" + std::to_string(mem_addr) + "] is out of range.\n");
    }
    os << main_memory[mem_addr] << std::endl;
}

#endif
