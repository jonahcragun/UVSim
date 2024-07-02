#ifndef QT_OUTPUT_H
#define QT_OUTPUT_H

#include "output_handler.h"
#include <functional>
#include <vector>
#include <string>

class QtOutputHandler: public OutputHandler {
public:
    QtOutputHandler(std::function<void(const std::string&)> console);
    ~QtOutputHandler();

    void handle_output() override;

    void export_instructions_to_file(const std::vector<std::string>& instructions);

private:
    std::function<void(const std::string&)> console;
};

#endif
