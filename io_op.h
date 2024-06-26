#ifndef IO_OP_H
#define IO_OP_H

#include "output_handler.h"
#include <iostream>
#include <string>
#include <stdexcept>

// read word into specified memory index of main_memory
template <size_t SIZE>
void read(std::istream& is, short (&main_memory)[SIZE], short mem_addr) {
    bool size_warning = false;
    if (mem_addr < 0 || mem_addr >= SIZE) {
        throw std::out_of_range("READ Error: Memory address [" + std::to_string(mem_addr) + "] is out of range.");
    }
    std::string input;
    is >> input;

    if(input.length() > 5){
        size_warning = true;
    }

    if (input.length() > 4) {
        if (input[0] == '-' || input[0] == '+') {
            // Only keep the first 5 characters
            input = input.substr(0, 5);
        } else {
            // Only keep the first 4 characters
            input = input.substr(0, 4);
        }
    }
    try{
        for (size_t i = 0; i < input.length(); ++i) {
            char c = input[i];
            if (i == 0 && (c == '-' || c == '+')) {
                continue;
            }
            if (!isdigit(c)) {
                if (size_warning) {
                    throw std::runtime_error("Warning: Input too large. Only the first signed numeric sequence of 4 digits will be stored.\nREAD Error: Invalid format '" + input + '\'');
                }
                throw std::runtime_error("READ Error: Invalid format '" + input + '\'');
            }
        }
        main_memory[mem_addr] = std::stoi(input);
    } catch (const std::invalid_argument& e) {
        if (size_warning) {
            throw std::runtime_error("Warning: Input too large. Only the first signed numeric sequence of 4 digits will be stored.\nREAD Error: Invalid input '" + input + '\'');
        }
        throw std::runtime_error("READ Error: Invalid input '" + input + '\'');
    }
    if (size_warning) {
        throw std::length_error("Warning: Input too large. Only the first signed numeric sequence of 4 digits will be stored.");
    }
}

// write word from specified memory index to terminal
template <size_t SIZE>
void write(std::ostream& os, short (&main_memory)[SIZE], short mem_addr) {
    if (mem_addr < 0 || mem_addr >= SIZE) {
        throw std::out_of_range("WRITE Error: Memory address [" + std::to_string(mem_addr) + "] is out of range.");
    }
    os << main_memory[mem_addr] << std::endl;
}

template <size_t SIZE>
void write(OutputHandler& os, short (&main_memory)[SIZE], short mem_addr) {
    if (mem_addr < 0 || mem_addr >= SIZE) {
        throw std::out_of_range("WRITE Error: Memory address [" + std::to_string(mem_addr) + "] is out of range.");
    }
    os << main_memory[mem_addr] << std::endl;
}

#endif
