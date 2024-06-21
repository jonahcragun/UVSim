#ifndef CONSOLE_OUTPUT_H
#define CONSOLE_OUTPUT_H

#include "output_handler.h"
#include <iostream>

class ConsoleOutputHandler: public OutputHandler {
public:
    void handle_output() override;
};

#endif