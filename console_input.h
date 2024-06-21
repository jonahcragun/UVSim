#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include "input_handler.h"

class ConsoleInputHandler : public InputHandler {
public:
    std::istream& get_user_input() override;
    std::vector<std::string> get_instructions() override;
};

#endif
