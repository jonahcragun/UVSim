#include "output_handler.h"

OutputHandler& OutputHandler::operator<<(std::ostream& (*manip)(std::ostream&)) {
    if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
        // Call display_output when std::endl is encountered
        buffer << manip;
        handle_output();
        buffer.str("");
    } else {
        buffer << manip;
    }
    return *this;
}

std::ostream& OutputHandler::pass_buffer(){
    return buffer;
}