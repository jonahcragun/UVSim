#ifndef uvsim_input_h
#define uvsim_input_h

#include <iostream>
#include <vector>
#include <string>

class UVSim_Input{
public:
    std::vector<std::string> split_lines(std::istream& is);
    std::vector<std::string> prompt_console_file_input();
};

#endif
