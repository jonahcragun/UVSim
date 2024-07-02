#include "output_handler.h"

OutputHandler& OutputHandler::operator<<(std::ostream& (*manip)(std::ostream&)) {
    buffer << manip;
    return *this;
}

std::ostream& OutputHandler::pass_buffer(){
    return buffer;
}
