#include "qt_output.h"

void QtOutputHandler::handle_output(){
    console(buffer.str());
    buffer.clear();
    buffer.str("");
};

QtOutputHandler::QtOutputHandler(std::function<void(const std::string&)> console_func)
    : console(console_func) {}
