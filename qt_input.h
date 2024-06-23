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
    std::istream& get_user_input() override;
    std::vector<std::string> get_instructions() override;
    ~QtInputHandler();

    void set_input_data(const std::string& data);
    void set_instr_data(const std::vector<std::string>& data);
    void tie_input_ui(InputDialog& input_ui);
    QtInputHandler(std::function<void(const std::string&)> console);

protected:
    InputDialog* userInput = nullptr;
    std::function<void(const std::string&)> console;
    QEventLoop inputEventLoop;
};

#endif
