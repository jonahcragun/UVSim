#include "test.h"
#include "uvsim.h"
#include "constants.h"
#include "io_op.h"
#include "memory_op.h"
#include "arithmetic_op.h"
#include "control_op.h"

#include <stdexcept>

using std::exception;

void case_one() {
    
};
void case_two() {
    
};
void case_three() {
    
};

int main() {
    try {
        case_one();
        case_two();
        case_three();
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
