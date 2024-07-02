#ifndef QT_INPUT_H
#define QT_INPUT_H

#include "input_handler.h"
#include "inputdialog.h"
#include <iostream>
#include <vector>
#include <string>
#include <QEventLoop>

class QtInputHandler : public InputHandler {
public:
    QtInputHandler(std::function<void(const std::string&)> console);
    ~QtInputHandler();

    std::istream& get_user_input() override;
    std::vector<std::string> get_instructions() override;

    std::vector<std::string> import_instructions_from_file();

    void set_input_data(const std::string& data);
    void set_instr_data(std::vector<std::string>& data);
    void tie_input_ui(InputDialog& input_ui);

protected:
    InputDialog* userInput = nullptr;
    std::function<void(const std::string&)> console;
    QEventLoop inputEventLoop;
};

#endif
