#include "uvsim_input.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

void UVSim_Input::read_from_stream(std::istream& is, short* main_memory){
    if (!is) {
        throw std::runtime_error("READ_FILE Error: Invalid file entered");
    }

    std::string line;
    unsigned short i = 0;

    while (std::getline(is, line)) {
        if (i > MEMORY_SIZE - 1)
            throw std::runtime_error("READ_FILE Error: File is too long: cannot exceed " + std::to_string(MEMORY_SIZE) + " lines");

        if (line.empty()) {
            continue;
        } else if (line.length() > 4) {
            if (line[0] == '-' || line[0] == '+')
                line = line.substr(0, 5); // Only keep the first 5 characters
            else
                line = line.substr(0, 4); // Only keep the first 4 characters
        }

        try {
            for (int j = 0; j < line.length(); ++j) {
                char c = line[j];
                if (j == 0 && (c == '-' || c == '+')) {
                    continue;
                }
                if (!isdigit(c)) {
                    throw std::runtime_error("READ_FILE Error: Invalid format '" + line + "' at line " + std::to_string(i));
                }
            }
            main_memory[i] = std::stoi(line);
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("READ_FILE Error: Invalid format '" + line + "' at line " + std::to_string(i));
        }

        ++i;
    }
};


void UVSim_Input::read_file(short* main_memory){
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

    read_from_stream(ifs, main_memory);

    ifs.close();
};
