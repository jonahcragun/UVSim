#include "uvsim.h"
#include "uvsim_input.h"

#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
	// run UVSim
	try {
        UVSim_Input input;
        UVSim run_prog;

        std::vector<std::string> instructions = input.prompt_console_file_input();
        run_prog.run(instructions);
	}
	catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
	}

    return 0;
}
