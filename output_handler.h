#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include <iostream>
#include <sstream>

class OutputHandler {
public:
    virtual ~OutputHandler() = default;

    virtual void handle_output() = 0;

    std::ostream& pass_buffer();

    template <typename T>
    OutputHandler& operator<<(const T& value) {
        buffer << value;
        return *this;
    }

    OutputHandler& operator<<(std::ostream& (*manip)(std::ostream&));

protected:
    std::ostringstream buffer;
};

#endif