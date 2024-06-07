#include "uvsim.h"

#include <iostream>
#include <stdexcept>

int main() {
	// run UVSim
	try {
		UVSim run_prog;
        run_prog.run();
	}
	catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
	}

    return 0;
}
