#include "test.h"
#include "uvsim.h"
#include "constants.h"
#include "io_op.h"
#include "memory_op.h"
#include "arithmetic_op.h"
#include "control_op.h"
#include <stdexcept>
#include <iostream>

using std::exception;

void case_one() {
    // Add Case One
    short accumulator = 0;
    short main_memory[10];
    main_memory[3] = 10;
    short mem_addr = 3;
    add(accumulator, main_memory, mem_addr);
    if (accumulator != 10) {
        throw std::logic_error("Add Function did not correctly add from memory");
    }
};

void case_two() {
    bool did_catch = false;
    try {
        short accumulator = 10;
        short main_memory[10];
        short mem_addr = 100;
        add(accumulator, main_memory, mem_addr);
    }
    catch(std::exception& e) {
        did_catch = true;
    }
    if (!did_catch) {
        throw std::range_error("Add block did not throw the correct error when index out of range.");
    }
};

void case_three() {
    // Subtract Case One
    short accumulator = 10;
    short main_memory[10];
    main_memory[4] = 8;
    short mem_addr = 4;
    subtract(accumulator, main_memory, mem_addr);
    if (accumulator != 2) {
        throw std::logic_error("Subtract Function did not correctly subtract from memory");
    }
};

void case_four() {
    bool did_catch = false;
    try {
        short accumulator = 10;
        short main_memory[10];
        short mem_addr = 100;
        subtract(accumulator, main_memory, mem_addr);
    }
    catch(std::exception& e) {
        did_catch = true;
    }
    if (!did_catch) {
        throw std::range_error("Subtract block did not throw the correct error when index out of range.");
    }
}

void case_five() {
    // Branch Cases
    short br_target = 12;
    if (branch(br_target) != 12) {
        throw std::logic_error("Branch function did not return the correct target.");
    }
};

void case_six() {
    bool did_catch = false;
    try {
        short mem_addr = 100;
        branch(mem_addr);
    }
    catch(std::exception& e) {
        did_catch = true;
    }
    if (!did_catch) {
        throw std::range_error("Branch block did not throw the correct error when index out of range.");
    }
};

int main() {
    try {
        case_one();
        case_two();
        case_three();
        case_four();
        case_five();
        case_six();
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
