#ifndef MEMORY_OP_H
#define MEMORY_OP_H

void load(short& accumulator, const short (&main_memory)[100], short mem_addr);
void store(short& accumulator, short (&main_memory)[100], short mem_addr);

#endif