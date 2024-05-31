#include "test.h"
#include "uvsim.h"
#include "arithmetic_op.h"
#include "control_op.h"
#include <stdexcept>
#include <iostream>

using std::exception;

void case_one() { // Add Case One
    short accumulator = 0;
    short main_memory[10];
    main_memory[3] = 10;
    short mem_addr = 3;
    add(accumulator, main_memory, mem_addr);
    if (accumulator != 10) {
        throw std::logic_error("Add Function did not correctly add from memory");
    }
};

void case_two() { // Add Case Two
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

void case_three() { // Subtract Case One
    short accumulator = 10;
    short main_memory[10];
    main_memory[4] = 8;
    short mem_addr = 4;
    subtract(accumulator, main_memory, mem_addr);
    if (accumulator != 2) {
        throw std::logic_error("Subtract Function did not correctly subtract from memory");
    }
};

void case_four() { // Subtract Case Two
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

void case_five() { // Branch Case One
    short br_target = 12;
    if (branch(br_target) != 12) {
        throw std::logic_error("Branch function did not return the correct target.");
    }
};

void case_six() { // Branch Case Two
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
void case_seven() { // Case One
    
}

void case_eight() { // Case Two
    
}

void case_nine() { // Case One
    
}

void case_ten() { // Case Two
    
}

void case_eleven() { // Case One
    
}

void case_twelve() { // Case Two
    
}

void case_thirteen() { // Case One
    
}

void case_fourteen() { // Case Two
    
}

void case_fifteen() { // Case One
    
}

void case_sixteen() { // Case Two
    
}

void case_seventeen() { // Case One
    
}

void case_eighteen() { // Case Two
    
}

void case_nineteen() { // Case One
    
}

void case_twenty() { // Case Two
    
}

void case_twentyone() { // Case One
    
}

void case_twentytwo() { // Case Two
    
}

void case_twentythree() { // Case One
    
}

void case_twentyfour() { // Case Two
    
}


int main() {
    try {
        case_one();
        case_two();
        case_three();
        case_four();
        case_five();
        case_six();
        // case_seven();
        // case_eight();
        // case_nine();
        // case_ten();
        // case_eleven();
        // case_twelve();
        // case_thirteen();
        // case_fourteen();
        // case_fifteen();
        // case_sixteen();
        // case_seventeen();
        // case_eighteen();
        // case_nineteen();
        // case_twenty();
        // case_twentyone();
        // case_twentytwo();
        // case_twentythree();
        // case_twentyfour();
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
