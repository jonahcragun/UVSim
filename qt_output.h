#ifndef QT_OUTPUT_H
#define QT_OUTPUT_H

#include "output_handler.h"
#include <functional>
#include <string>

class QtOutputHandler: public OutputHandler {
public:
    void handle_output() override;
    QtOutputHandler(std::function<void(const std::string&)> console);

private:
    std::function<void(const std::string&)> console;
};

#endif
