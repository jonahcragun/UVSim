#include "qt_input.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

QtInputHandler::QtInputHandler(std::function<void(const std::string&)> console_func)
    : console(console_func) {}

QtInputHandler::~QtInputHandler(){
    inputEventLoop.quit();
}

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

    inputEventLoop.quit();
}

void QtInputHandler::set_instr_data(const std::vector<std::string>& data) {
    std::ostringstream passthrough;
    instr_buffer.str("");
    for (const std::string& s : data){
        passthrough << s << std::endl;
    }
    instr_buffer.str(passthrough.str());
    instr_buffer.clear();
    std::cout << "NEW INSTRUCTIONS IN INPUTHANDLER AFTER set_instr_data" << std::endl << instr_buffer.str() << std::endl;
}

std::vector<std::string> QtInputHandler::get_instructions() {
    std::vector<std::string> instructions;
    std::string line;
    std::cout << "INSTRUCTIONS IN INPUTHANDLER WHEN get_instructions CALLED" << std::endl << instr_buffer.str() << std::endl;
    while (std::getline(instr_buffer, line)) {
        instructions.push_back(line);
    }
    return instructions;
}

void QtInputHandler::tie_input_ui(InputDialog& input_ui) {
    userInput = &input_ui;
}
