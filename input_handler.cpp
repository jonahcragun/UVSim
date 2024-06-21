#include "input_handler.h"

std::vector<std::string> InputHandler::split_lines(std::istream& is){
    if (!is) {
        throw std::runtime_error("READ_FILE Error: Invalid file entered");
    }

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(is, line)) {
        lines.push_back(line);
    }
    return lines;
};
