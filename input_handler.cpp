#include "input_handler.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <cctype>

bool isInstr(std::string& instruction){
    bool is_instruction = false;
    int numeric_instruction = std::stoi(instruction);
    int op_code = numeric_instruction / 100;
    switch (op_code) {
        case 10: // 10: READ
            is_instruction = true;
            break;
        case 11: // 11: WRITE
            is_instruction = true;
            break;
        case 20: // 20: LOAD
            is_instruction = true;
            break;
        case 21: // 21: STORE
            is_instruction = true;
            break;
        case 30: // 30: ADD
            is_instruction = true;
            break;
        case 31: // 31: SUBTRACT
            is_instruction = true;
            break;
        case 32: // 32: DIVIDE
            is_instruction = true;
            break;
        case 33: // 33: MULTIPLY
            is_instruction = true;
            break;
        case 40: // 40: BRANCH
            is_instruction = true;
            break;
        case 41: // 41: BRANCHNEG
            is_instruction = true;
            break;
        case 42: // 42: BRANCHZERO
            is_instruction = true;
            break;
        case 43: // 43: HALT
            is_instruction = true;
            break;
        default: // INVALID OPCODE
            break;
    }
    return is_instruction;
}


std::vector<std::string> InputHandler::split_lines(std::istream& is) {
    if (!is) {
        throw std::runtime_error("Split lines Error: Invalid istream passed.\n");
    }

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(is, line)) {
        lines.push_back(line);
    }
    return lines;
}

void InputHandler::validate_instruction(std::string& instruction) {
    std::ostringstream throw_context;
    bool has_error = false; // Flag to track if any error occurs

    try {
        validate_format(instruction); // First format validation attempt
    } catch (const std::length_error& size_warning) {
        // Handle size warning, instruction should have been resized due to pass by reference
        throw_context << size_warning.what() << std::endl;
        has_error = true;

        try {
            validate_format(instruction); // Second format validation attempt
        } catch (const std::invalid_argument& conversion_error) {
            // Catching second format validation where instruction is now resized but also has a bad instruction
            throw_context << conversion_error.what() << std::endl;
            instruction = "0"; // Setting the instruction to 0 for further processing
        }
    } catch (const std::invalid_argument& conversion_error) {
        // Catching first format validation with bad instruction
        throw_context << conversion_error.what() << std::endl;
        instruction = "0"; // Setting the instruction to 0 for further processing
        has_error = true;
    }

    try {
        validate_numeric(instruction); // Numeric Validation attempt
    } catch (const std::exception& e) {
        // Catching any exception that doesn't need special handling.
        throw_context << e.what() << std::endl;
        has_error = true;
    }

    if (has_error) {
        throw std::runtime_error(throw_context.str());
    }
}

void InputHandler::validate_format(std::string& instruction) {
    instruction.erase(std::remove_if(instruction.begin(), instruction.end(), ::isspace), instruction.end());
    // Handling for instruction empty string
    if (instruction.empty()) {
        throw std::invalid_argument("Validation Error: Instruction is empty.\n");
    }
    std::string original_instruction = instruction;
    size_t instruction_length = instruction.length();

    if (instruction_length == 1){
        char c = instruction[0];
        if (!isdigit(c)) {
            throw std::invalid_argument(
                "Validation Error: Invalid format '" + instruction + "'. Must be a sequence of 4 or 6 digits.");
        }
    }

    // Handling for instruction string size greater than 6 char with bad format or greater than 7 char with good format
    bool size_warning = false;
    if (instruction_length >= 6) {
        if (instruction[0] == '-' || instruction[0] == '+') {
            // Only keep the first 7 characters
            instruction = instruction.substr(0, 7);
            size_warning = (instruction_length > 7) ? true : false;
        } else {
            // Only keep the first 6 characters
            instruction = instruction.substr(0, 6);
            size_warning = (instruction_length > 6) ? true : false;
        }
    }
    if (size_warning) {
        std::ostringstream warning;
        warning << "Warning: Input character count too large. Only the first 4 signed digits sequence: '"
                << instruction << "' from '" << original_instruction << "' will attempt to be stored.\n";
        throw std::length_error(warning.str());
    }
    // Check if instruction is a 4 digit instruction
    if (instruction_length >= 4 and instruction_length < 6) {
        bool is_instruction;
        std::string temp_instruction;
        if (instruction[0] == '-' || instruction[0] == '+') {
            temp_instruction = instruction.substr(1, 4);
        }
        else {
            temp_instruction = instruction.substr(0, 4);
        }
        is_instruction = ::isInstr(temp_instruction);
        if (is_instruction) {
            std::string zero = "0";
            if (instruction[0] == '-' || instruction[0] == '+') {
                std::string instruction_sign = instruction.substr(0, 1);
                std::string instruction_bits = instruction.substr(1, 2);
                std::string instruction_mem = instruction.substr(3, 2);
                instruction = instruction_sign + zero + instruction_bits + zero + instruction_mem;
            }
            else {
                std::string instruction_bits = instruction.substr(0, 2);
                std::string instruction_mem = instruction.substr(2, 2);
                instruction = zero + instruction_bits + zero + instruction_mem;
            }
        }
        else {
            std::string zeroes = "00";
            if (instruction[0] == '-' || instruction[0] == '+') {
                std::string instruction_sign = instruction.substr(0, 1);
                instruction = instruction.substr(1, 4);
                instruction = instruction_sign + zeroes + instruction;
            }
            else {
                instruction = zeroes + instruction;
            }
        }
    }
    // Validate each character in the instruction string
    for (size_t i = 0; i < instruction_length; ++i) {
        char c = instruction[i];
        if (i == 0 && (c == '-' || c == '+')) {
            continue;
        }
        if (!isdigit(c)) {
            throw std::invalid_argument(
                "Validation Error: Invalid format found '" + instruction + "'. Must be a signed 4 digit sequence.");
        }
    }
}

void InputHandler::validate_numeric(std::string& instruction) {
    if (instruction.empty()) {
        throw std::runtime_error("Validation Error: Instruction is empty.");
    }
    try {
        int numeric_instruction = std::stoi(instruction);
        std::ostringstream os;
        os << (numeric_instruction >= 0 ? '+' : '-');
        os << std::setw(6) << std::setfill('0') << std::abs(numeric_instruction);
        instruction = os.str();
    } catch (const std::invalid_argument& stoi_err) {
        std::ostringstream throw_context;
        throw_context << "Validation Error: Invalid input, could not convert '" << instruction << "' to numeric value.";
        throw std::invalid_argument(throw_context.str());
    } catch (const std::out_of_range& stoi_err) {
        std::ostringstream throw_context;
        throw_context << "Validation Error: Invalid input, numeric value '" << instruction << "' is out of conversion range.";
        throw std::out_of_range(throw_context.str());
    }
}
