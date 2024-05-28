#include "ls_op.h"
#include <iostream>

// Load a word from a specific location in memory into the accumulator.
void load(short& accumulator, const short (&main_memory)[100], short mem_addr) {
  if (mem_addr >=0 && mem_addr < 100){
    accumulator = main_memory[mem_addr];
  } 
  else{
    // Handle error: invalide address
    std::cerr << "Error: Invalid memory address for load operation." << std::endl;
    // For simplicity, let's just set the accumulator to 0
    accumulator = 0;
  }
}
