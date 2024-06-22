#include "control_op.h"
#include "constants.h"
#include <string>

#include <stdexcept>

short halt() {
	return MEMORY_SIZE;
}

// If the accumulator is a negative value, return to the potential memory address. Else return the current memory address incremented
short branchNeg(short& accumulator, short cur_addr, short br_target) {
    if (br_target < 0 || br_target >= MEMORY_SIZE) {
        throw std::out_of_range("BRANCHNEG Error: Memory address " + std::to_string(br_target) + " is out of range.");
    }
    return (accumulator < 0) ? br_target : ++cur_addr;
}

// If the accumulator equals zero, return to the potential memory address. Else return the current memory address incremented
short branchZero(short& accumulator, short cur_addr, short br_target){
    if (br_target < 0 || br_target >= MEMORY_SIZE) {
        throw std::out_of_range("BRANCHZERO Error: Memory address " + std::to_string(br_target) + " is out of range.");
    }
    return (accumulator == 0) ? br_target : ++cur_addr;
}

// Return the memory address to switch the current memory address
short branch(short br_target) {
    if (br_target < 0 || br_target >= MEMORY_SIZE) {
        throw std::out_of_range("BRANCH Error: Memory address " + std::to_string(br_target) + " is out of range.");
    }
    return br_target;
}
