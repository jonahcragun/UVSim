#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <vector>
#include <string>
#include <istream>

class InputHandler {
public:
    virtual ~InputHandler() = default;

    virtual std::istream& get_user_input() = 0;
    virtual std::vector<std::string> get_instructions() = 0;

    static std::vector<std::string> split_lines(std::istream& is);
};

#endif