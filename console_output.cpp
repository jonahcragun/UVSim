#include "console_output.h"

void ConsoleOutputHandler::handle_output() {
    std::cout << buffer.str();
}