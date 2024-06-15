#include "uvsim_input.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

std::vector<std::string> UVSim_Input::read_from_stream(std::istream& is){
    if (!is) {
        throw std::runtime_error("READ_FILE Error: Invalid file entered");
    }

    std::string line;
    unsigned short i = 0;
    std::vector<std::string> lines;
    while (std::getline(is, line)) {
        lines.push_back(line);
    }
    return lines;
};


std::vector<std::string> UVSim_Input::read_file(){
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

    std::vector<std::string> lines = read_from_stream(ifs);

    ifs.close();
    return lines;
};
