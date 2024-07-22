#ifndef CONTROL_OP_H
#define CONTROL_OP_H

int halt();
int branchNeg(int& accumulator, int cur_addr, int br_target);
int branchZero(int& accumulator, int cur_addr, int br_target);
int branch(int br_target);

#endif
