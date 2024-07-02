#include "input_handler.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>

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
                "Validation Error: Invalid format '" + instruction + "'. Must be a sequence of 4 digits.");
        }
    }

    // Handling for instruction string size greater than 4 char with bad format or greater than 5 char with good format
    bool size_warning = false;
    if (instruction_length > 4) {
        if (instruction[0] == '-' || instruction[0] == '+') {
            // Only keep the first 5 characters
            instruction = instruction.substr(0, 5);
            size_warning = (instruction_length > 5) ? true : false;
        } else {
            // Only keep the first 4 characters
            instruction = instruction.substr(0, 4);
            size_warning = (instruction_length > 4) ? true : false;
        }
    }
    if (size_warning) {
        std::ostringstream warning;
        warning << "Warning: Input character count too large. Only the first 4 signed digits sequence: '"
                << instruction << "' from '" << original_instruction << "' will attempt to be stored.\n";
        throw std::length_error(warning.str());
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
        os << std::setw(4) << std::setfill('0') << std::abs(numeric_instruction);
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
