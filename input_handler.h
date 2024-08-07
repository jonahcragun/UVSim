#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <vector>
#include <string>
#include <istream>
#include <sstream>

class InputHandler {
public:
    virtual ~InputHandler() = default;

    virtual std::istream& get_user_input() = 0;
    virtual std::vector<std::string> get_instructions() = 0;

    static std::vector<std::string> split_lines(std::istream& is);
    static void validate_instruction(std::string& instruction);

protected:
    std::ostringstream input_buffer;
    std::istringstream user_input_buffer;
    std::istringstream instr_buffer;

private:
    static void validate_format(std::string& instruction);
    static void validate_numeric(std::string& instruction);
};

#endif
