#include "uvsim.h"

#include <iostream>
#include <stdexcept>

using std::exception;
using std::cerr;
using std::endl;

int main() {
	// run UVSim
	try {
		UVSim run_prog;
        run_prog.run();
	}
	catch(exception& e) {
		cerr << e.what() << endl;
	}

    return 0;
}
