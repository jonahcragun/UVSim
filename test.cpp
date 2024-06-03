#include "test.h"
#include "uvsim.h"
#include "constants.h"
#include "arithmetic_op.h"
#include "control_op.h"
#include "memory_op.h"
#include "io_op.h"
#include <stdexcept>

using std::exception;

UVSim uvsim;
/*
Reference to be able to call the execute_op( opcode, mem_addr, cur_addr) function
OPCODES:
10: Read
11: Write
20: Load
21: Store
30: Add
31: Subtract
32: Divide
33: Multiply
40: Branch
41: BranchNeg
42: BranchZero
43: Halt
*/

void case_one() { // Add Case One
    short* memory = uvsim.get_memory();
    short mem_addr = 3;
    short expected_result = 15;

    uvsim.set_memory_address(mem_addr, 7);
    uvsim.set_accumulator(8);
    TEST_FUNCTION("CASE 1.0: Testing UVSim execution_op function with add opcode, confirming run without error.",
                  uvsim.execute_op(30, mem_addr, 0));

    short result1 = uvsim.get_accumulator();
    TEST("CASE 1.1: Testing addition result of UVSim execution_op is equal to expected result.",
         result1 == expected_result,
         "Failed to return the expected value of 2, got: " + std::to_string(result1));

    uvsim.set_accumulator(8);
    TEST_FUNCTION("CASE 1.2: Testing add function is correctly adding from memory",
                  add(uvsim.get_accumulator(), memory, mem_addr));

    short result2 = uvsim.get_accumulator();
    TEST("CASE 1.3: Testing addition result of add function is equal to expected result.",
         result2 == expected_result,
         "Failed to return the expected value of 2, got: " + std::to_string(result2));

    TEST("CASE 1.4: Comparing UVSim execution_op and add function results.",
         result1 == result2,
         "Failed comparison of " + std::to_string(result1) + " and " + std::to_string(result2) + ".");
}

void case_two() { // Add Case Two
    short out_of_range_addr = MEMORY_SIZE + 1;
    short memory[10];
    short temp_accumulator = 10;
    EXCEPTION_TEST_FUNC("CASE 2.0: Testing UVSim execution_op function add opcode will correctly throw an error when index out of range.",
                        uvsim.execute_op(30, out_of_range_addr, 0),
                        std::out_of_range);

    EXCEPTION_TEST_FUNC("CASE 2.1: Testing UVSim execution_op function add opcode will correctly throw an error when index out of range.",
                        add(temp_accumulator, memory, out_of_range_addr),
                        std::out_of_range);
}

void case_three() { // Subtract Case One
    short* memory = uvsim.get_memory();
    short mem_addr = 4;
    short expected_result = 2;

    uvsim.set_memory_address(mem_addr, 8);
    uvsim.set_accumulator(10);
    TEST_FUNCTION("CASE 3.0: Testing UVSim execution_op function with subtract opcode, confirming run without error.",
                  uvsim.execute_op(31, mem_addr, 0));

    short result1 = uvsim.get_accumulator();
    TEST("CASE 3.1: Testing subtraction result of UVSim execution_op is equal to expected result.",
         result1 == expected_result,
         "Failed to return the expected value of 2, got: " + std::to_string(result1));

    uvsim.set_accumulator(10);
    TEST_FUNCTION("CASE 3.2: Testing subtract function is correctly subtracting from memory",
                  subtract(uvsim.get_accumulator(), memory, mem_addr));

    short result2 = uvsim.get_accumulator();
    TEST("CASE 3.3: Testing subtraction result of subtract function is equal to expected result.",
         result2 == expected_result,
         "Failed to return the expected value of 2, got: " + std::to_string(result2));

    TEST("CASE 3.4: Comparing UVSim execution_op and subtract function results.",
         result1 == result2,
         "Failed comparison of " + std::to_string(result1) + " and " + std::to_string(result2) + ".");
}

void case_four() { // Subtract Case Two
    short mem_addr = 100;
    EXCEPTION_TEST_FUNC("CASE 4: Testing subtract function to correctly throw an error when index out of range.",
                        uvsim.execute_op(31, mem_addr, 0),
                        std::out_of_range);
}

void case_five() { // Branch Case One
    short br_target = 12;
    TEST("CASE 5.1: Testing UVSim execute_op function to correctly return the target memory address.",
            uvsim.execute_op(40, br_target, 0) == br_target);

    TEST("CASE 5.2: Testing branch function to correctly return the target memory address.",
            branch(br_target) == br_target);
}

void case_six() { // Branch Case Two
    short br_target = 100;
    EXCEPTION_TEST_FUNC("CASE 6: Testing branch function to correctly throw an error when index out of range.",
                        uvsim.execute_op(40, br_target, 0),
                        std::out_of_range);
}

void case_seven() { // Branch Negative Case One
    short br_target = 12;
    uvsim.set_accumulator(-5); // Set accumulator to a negative value
    TEST("CASE 7.1: Testing UVSim execute_op function with branch negative opcode to correctly return the target memory address.",
         uvsim.execute_op(41, br_target, 0) == br_target);

    TEST_FUNCTION("CASE 7.2: Testing branchNeg function to correctly return the target memory address when accumulator is negative.",
                  branchNeg(uvsim.get_accumulator(), 0, br_target));

    short result = branchNeg(uvsim.get_accumulator(), 0, br_target);
    TEST("CASE 7.3: Testing branchNeg result is equal to expected result.",
         result == br_target,
         "Failed to return the expected value of " + std::to_string(br_target) + ", got: " + std::to_string(result));
}


void case_eight() { // Branch Negative Case Two
    short out_of_range_addr = MEMORY_SIZE + 1;
    uvsim.set_accumulator(-5); // Set accumulator to a negative value
    EXCEPTION_TEST_FUNC("CASE 8: Testing UVSim execute_op function with branch negative opcode to correctly throw an error when index out of range.",
                        uvsim.execute_op(41, out_of_range_addr, 0),
                        std::out_of_range);
}


void case_nine() { // Branch Zero Case One
    short br_target = 12;
    uvsim.set_accumulator(0); // Set accumulator to zero
    TEST("CASE 9.1: Testing UVSim execute_op function with branch zero opcode to correctly return the target memory address.",
         uvsim.execute_op(42, br_target, 0) == br_target);

    TEST_FUNCTION("CASE 9.2: Testing branchZero function to correctly return the target memory address when accumulator is zero.",
                  branchZero(uvsim.get_accumulator(), 0, br_target));

    short result = branchZero(uvsim.get_accumulator(), 0, br_target);
    TEST("CASE 9.3: Testing branchZero result is equal to expected result.",
         result == br_target,
         "Failed to return the expected value of " + std::to_string(br_target) + ", got: " + std::to_string(result));
}


void case_ten() { // Branch Zero Case Two
    short out_of_range_addr = MEMORY_SIZE + 1;
    uvsim.set_accumulator(0); // Set accumulator to zero
    EXCEPTION_TEST_FUNC("CASE 10: Testing UVSim execute_op function with branch zero opcode to correctly throw an error when index out of range.",
                        uvsim.execute_op(42, out_of_range_addr, 0),
                        std::out_of_range);
}


void case_eleven() { // Store Case One
    short* memory = uvsim.get_memory();
    short mem_addr = 5;
    short value_to_store = 10;
    uvsim.set_accumulator(value_to_store);
    TEST_FUNCTION("CASE 11.1: Testing UVSim execute_op function with store opcode to correctly store the accumulator value.",
                  uvsim.execute_op(21, mem_addr, 0));

    short stored_value = uvsim.get_memory_value(mem_addr);
    TEST("CASE 11.2: Testing stored value in memory is equal to the accumulator value.",
         stored_value == value_to_store,
         "Failed to store the expected value of " + std::to_string(value_to_store) + ", got: " + std::to_string(stored_value));

    uvsim.set_accumulator(value_to_store);
    TEST_FUNCTION("CASE 11.3: Testing store function to correctly store the accumulator value in memory",
                  store(uvsim.get_accumulator(), memory, mem_addr));

    stored_value = uvsim.get_memory_value(mem_addr);
    TEST("CASE 11.4: Testing store function result is equal to expected result.",
         stored_value == value_to_store,
         "Failed to store the expected value of " + std::to_string(value_to_store) + ", got: " + std::to_string(stored_value));
}


void case_twelve() { // Store Case Two
    short out_of_range_addr = MEMORY_SIZE + 1;
    short value_to_store = 10;
    uvsim.set_accumulator(value_to_store);
    EXCEPTION_TEST_FUNC("CASE 12: Testing UVSim execute_op function with store opcode to correctly throw an error when index out of range.",
                        uvsim.execute_op(21, out_of_range_addr, 0),
                        std::out_of_range);
}


void case_thirteen() { // Case One

}

void case_fourteen() { // Case Two

}

void case_fifteen() { // Case One

}

void case_sixteen() { // Case Two

}

void case_seventeen() { // Case One

}

void case_eighteen() { // Case Two

}

void case_nineteen() { // Case One

}

void case_twenty() { // Case Two

}

void case_twentyone() { // Case One

}

void case_twentytwo() { // Case Two

}

void case_twentythree() { // Case One

}

void case_twentyfour() { // Case Two

}

// COMPILE COMMAND: g++ -o test test.cpp uvsim.cpp arithmetic_op.cpp control_op.cpp memory_op.cpp
// RUN COMMAND: (Linux, MacOS) ./test.out  (Windows) test.exe
int main() {
    TestHandler::get_instance().set_verbose(true); // Comment out this line if you want to see only failed tests

    int total_tests = 24;
    for (int i = 1; i <= total_tests; (TEST_REPORT(i), CLEAR_RESULTS(), ++i)) {
        switch (i) {
            case 1:
                case_one();
                break;
            case 2:
                case_two();
                break;
            case 3:
                case_three();
                break;
            case 4:
                case_four();
                break;
            case 5:
                case_five();
                break;
            case 6:
                case_six();
                break;
            case 7:
                 case_seven();
                break;
            case 8:
                 case_eight();
                break;
            case 9:
                 case_nine();
                break;
            case 10:
                 case_ten();
                break;
            case 11:
                 case_eleven();
                break;
            case 12:
                 case_twelve();
                break;
            case 13:
                 case_thirteen();
                break;
            case 14:
                 case_fourteen();
                break;
            case 15:
                 case_fifteen();
                break;
            case 16:
                 case_sixteen();
                break;
            case 17:
                 case_seventeen();
                break;
            case 18:
                 case_eighteen();
                break;
            case 19:
                 case_nineteen();
                break;
            case 20:
                 case_twenty();
                break;
            case 21:
                 case_twentyone();
                break;
            case 22:
                 case_twentytwo();
                break;
            case 23:
                 case_twentythree();
                break;
            case 24:
                 case_twentyfour();
                break;
            default:
                break;
        }
    }

    return 0;
}