#include "uvsim.h"
#include "console_input.h"
#include "console_output.h"

#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
	// run UVSim
    ConsoleInputHandler input_handler;
    ConsoleOutputHandler output_handler;

	try {
        UVSim run_prog(&input_handler, &output_handler);

        run_prog.run();
	}
	catch(std::exception& e) {
        output_handler << e.what() << std::endl;
	}

    return 0;
}
