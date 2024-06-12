#ifndef uvsim_input_h
#define uvsim_input_h

#include <iostream>
#include "constants.h"

class UVSim_Input{
public:
    
    void read_file(short* main_memory);
    void read_from_stream(std::istream& is, short* main_memory);

};

#endif
