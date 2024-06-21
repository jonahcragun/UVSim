#include "qt_input.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::istream& QtInputHandler::get_user_input() {
    console("Enter a number: ");
    user_input_buffer.str("");
    user_input_buffer.clear();

    if (userInput && !userInput->isVisible()) {
        userInput->show();
    }

    inputEventLoop.exec();
    console(user_input_buffer.str());
    return user_input_buffer;
}

void QtInputHandler::set_input_data(const std::string& data) {
    user_input_buffer.str(data);
    user_input_buffer.clear();

    // Exit the event loop once data is set
    inputEventLoop.quit();
}

void QtInputHandler::set_instr_data(const std::vector<std::string>& data) {
    std::ostringstream passthrough;
    for (std::string s : data){
        passthrough << s << std::endl;
    }
    instr_buffer.str(passthrough.str());
}

std::vector<std::string> QtInputHandler::get_instructions() {
    std::vector<std::string> instructions;
    std::string line;
    while (std::getline(instr_buffer, line)) {
        instructions.push_back(line);
    }
    return instructions;
}

void QtInputHandler::tie_input_ui(InputDialog& input_ui) {
    userInput = &input_ui;
}

QtInputHandler::QtInputHandler(std::function<void(const std::string&)> console_func)
    : console(console_func) {}
