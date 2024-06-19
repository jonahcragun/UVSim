#include "uvsim.h"
#include "console_input.h"

#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
	// run UVSim
	try {
        ConsoleInputHandler input_handler;
        UVSim run_prog(&input_handler);

        run_prog.run();
	}
	catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
	}

    return 0;
}
