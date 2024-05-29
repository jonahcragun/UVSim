#include "control_op.h"

short halt() {
	return 100;
}

// If the accumulator is a negative value, return to the potential memory address. Else return the current memory address incremented
short branchNeg(short& accumulator, unsigned short& cur_addr, short& potential_addr){
    return (accumulator < 0) ? potential_addr : ++cur_addr;
}

// If the accumulator equals zero, return to the potential memory address. Else return the current memory address incremented
short branchZero(short& accumulator, unsigned short& cur_addr, short& potential_addr){
    return (accumulator == 0) ? potential_addr : ++cur_addr;
}