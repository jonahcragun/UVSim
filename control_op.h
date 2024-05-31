#ifndef CONTROL_OP_H
#define CONTROL_OP_H

short halt();
short branchNeg(short& accumulator, unsigned short& cur_addr, short& br_target);
short branchZero(short& accumulator, unsigned short& cur_addr, short& br_target);
short branch(short& br_target);

#endif
