#ifndef CONTROL_OP_H
#define CONTROL_OP_H

short halt();
short branchNeg(short& accumulator, unsigned short& cur_addr, short& potential_addr);
short branchZero(short& accumulator, unsigned short& cur_addr, short& potential_addr);
short branch(short& mem_addr);

#endif
