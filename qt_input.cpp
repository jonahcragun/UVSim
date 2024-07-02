#include "qt_input.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QStandardPaths>
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
    console("Input received: " + user_input_buffer.str() + "\n");
    return user_input_buffer;
}

void QtInputHandler::set_input_data(const std::string& data) {
    user_input_buffer.str(data);
    user_input_buffer.clear();

    inputEventLoop.quit();
}

void QtInputHandler::set_instr_data(std::vector<std::string>& data) {
    std::ostringstream passthrough;
    instr_buffer.str("");
    for (std::string& s : data){
        try {
            validate_instruction(s);
            // If validation is successful, add the line to instructions
            passthrough << s << std::endl;
        } catch (const std::exception& error) {
            std::ostringstream exception_context;
            exception_context << error.what() << " Skipping instruction." << std::endl;
            console(exception_context.str());
            continue;
        }
    }
    instr_buffer.str(passthrough.str());
    instr_buffer.clear();
}

std::vector<std::string> QtInputHandler::get_instructions() {
    std::vector<std::string> instructions;
    std::string line;
    while (std::getline(instr_buffer, line)) {
        try {
            validate_instruction(line);
            // If validation is successful, add the line to instructions
            instructions.push_back(line);
        } catch (const std::exception& error) {
            std::ostringstream exception_context;
            exception_context << error.what() << " Skipping instruction." << std::endl;
            console(exception_context.str());
            continue;
        }
    }
    return instructions;
}

void QtInputHandler::tie_input_ui(InputDialog& input_ui) {
    userInput = &input_ui;
}

std::vector<std::string> QtInputHandler::import_instructions_from_file(){
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString file_name = QFileDialog::getOpenFileName(
        nullptr, QObject::tr("Open File"), desktopPath, QObject::tr("Text Files (*.txt)"));
    if (!file_name.isEmpty()) {
        console("Attempting to import instructions from file: " + file_name.toStdString() + "...");
        QFile file(file_name);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString qstring_file_content = in.readAll();
            file.close();

            std::string string_file_content = qstring_file_content.toStdString();
            std::istringstream input_stream(string_file_content);
            std::vector<std::string> lines = split_lines(input_stream);
            return lines;
        } else {
            std::ostringstream throw_context;
            throw_context << "File read error: Unable to open " << file_name.toStdString() << std::endl;
            throw std::runtime_error(throw_context.str());
        }
    } else {
        std::ostringstream throw_context;
        throw_context << "File read error: No file provided" << std::endl;
        throw std::runtime_error(throw_context.str());
    }
}
