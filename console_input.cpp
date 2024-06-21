#include "console_input.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

std::istream& ConsoleInputHandler::get_user_input(){
    std::cout << "Enter a number: ";
    return std::cin;
}

std::vector<std::string> ConsoleInputHandler::get_instructions(){
    std::string file;
    std::cout << "Enter a BasicML file name: ";
    std::cin >> file;

    std::ifstream ifs(file);

    // Check if file is valid
    if (!ifs) {
        throw std::runtime_error("READ_FILE Error: Invalid file entered");
    }

    // Check if file is empty
    if (ifs.peek() == std::ifstream::traits_type::eof()) {
        throw std::runtime_error("READ_FILE Error: File is empty");
    }

    std::vector<std::string> lines = split_lines(ifs);

    ifs.close();
    return lines;
};
