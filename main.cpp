#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "io_op.h"
#include "memory_op.h"
#include "arithmetic_op.h"
#include "control_op.h"
#include "ls_op.h"

#define MEMORY_SIZE 100

using std::cout;
using std::endl;
using std::getline; 
using std::cin;
using std::ifstream;
using std::string;
using std::stoi;
using std::runtime_error;
using std::cerr;
using std::exception;
using std::to_string;

// UVSim VM that interprets BasicML (a simple machine language)
// has a memory array and accumulator register
class UVSim {
	short main_memory[MEMORY_SIZE];
	short accumulator;

	// read in file to memory starting at location 00
	void read_file() {
		string file;
		cout << "Enter a BasicML file name: ";
		cin >> file;
		

		ifstream ifs (file);
		
		// check if file is valid
		if (!ifs) {
			throw runtime_error("Invalid file entered");
		}

		string word;
		unsigned short i;

		while (getline(ifs, word)) {
			if (i > 99)
				throw runtime_error("File is too long: cannot exceed 100 lines");

			main_memory[i] = stoi(word);
			++i;
		}
	}

	// run program starting at memory location 00
	void execute() {
		unsigned short cur = 0;
		while (cur < MEMORY_SIZE) {
			short op_code;
			short mem_addr;

			split_instr(main_memory[cur], &op_code, &mem_addr);
			cur = execute_op(op_code, mem_addr, cur);
		}
	}

	// separate instruction into 2 parts, operation code and memory address
	// param 1: instruction
	// param 2: pointer to op code value
	// param 3: pointer to mem addr value
	void split_instr(short instr, short* op_code, short* mem_addr) {
		*op_code = instr / 100;
		*mem_addr = instr - (*op_code * 100);
	}

	// execute operation associated with op code 
	// return next memory address to run
	unsigned short execute_op(short op_code, short mem_addr, unsigned short cur) {
		if (op_code == 10) {
			read(accumulator, main_memory, mem_addr);
		}
		else if (op_code == 11) {
			write(accumulator, main_memory, mem_addr);
		}
		else if (op_code == 20) {
			load(accumulator, main_memory, mem_addr);
		}
		else if (op_code == 21) {

		}
		else if (op_code == 30) {

		}
		else if (op_code == 31) {

		}
		else if (op_code == 32) {
			divide(accumulator, main_memory, mem_addr);
		}
		else if (op_code == 33) {
			multiply(accumulator, main_memory, mem_addr);
		}
		else if (op_code == 40) {
            // return branch();
		}
		else if (op_code == 41) {

		}
		else if (op_code == 42) {

		}
		else if (op_code == 43) {
			cur = halt();
		}
		else {
			string e = "Invalid op code at address: " + to_string(cur);
			throw runtime_error(e); 
		}
		return ++cur;
	}
	
	// start VM, get user input for file name, load into memory, and execute program
	void run() {
		read_file();	
		execute();
	}

	public:

	UVSim() {
		run();
	}
	
};


int main() {
	// run UVSim
	try {
		UVSim run_prog;
	}
	catch(exception& e) {
		cerr << e.what() << endl;
	}

    return 0;
}
