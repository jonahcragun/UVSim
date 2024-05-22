#include <iostream>
#include "io_op.h"
#include "memory_op.h"
#include "arithmetic_op.h"
#include "control_op.h"

// UVSim VM that interprets BasicML (a simple machine language)
// has a memory array and accumulator register
class UVSim {
	short main_memory[100];
	short accumulator;

	public:
	// read in file to memory starting at location 00
	void read_file() {

	}

	// run program starting at memory location 00
	void run() {

	}

};

// read BasicML file into UVSim memory


int main() {
	UVSim run_prog;

    return 0;
}
