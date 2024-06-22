### UVSim Class Definition Document

This document provides an overview of the class design for the UVSim class design.

#### Classes and Their Responsibilities

1. **UVSim**
   - **Purpose**: Simulates a virtual machine that interprets BasicML (a simple machine language).
   - **Attributes**:
     - `short main_memory[MEMORY_SIZE]`: An array representing the machine's memory.
     - `short accumulator`: A register for arithmetic operations.
     - `InputHandler* input_handler`: Pointer to an input handler.
     - `OutputHandler*  output_handler`: Pointer to an output handler.
   - **Methods**:
     - `void reset_memory()`: Resets the memory and accumulator to initial states.
     - `void execute()`: Executes instructions loaded in memory.
     - `void split_instr(short instr, short* op_code, short* mem_addr)`: Splits an instruction into opcode and memory address.
     - `void parse_input(std::vector<std::string>& lines)`: Parses input lines into memory.
     - `unsigned short execute_op(short op_code, short mem_addr, short cur)`: Executes a single operation.
     - `short& get_accumulator()`: Returns the accumulator.
     - `short* get_memory()`: Returns the memory array.
     - `short get_memory_value(short mem_addr)`: Returns the value at a specific memory address
     - `void set_accumulator(short value)`: Sets the accumulator to a specific value.
     - `void set_memory_address(short mem_addr, short value)`: Sets a specific memory address to a value.
     - `void run()`: Runs the virtual machine 
     - `UVSim(InputHandler* handler_in, OutputHandler* handler_out)`: Constructor

2. **InputHandler (Abstract Class)**
   - **Purpose**: Abstract base class for handling user input.
   - **Methods**:
     - `virtual std::istream& get_user_input() = 0`: Pure virtual method to get user input.
     - `virtual std::vector<std::string> get_instructions() = 0`: Pure virtual method to get  instructions.
     - `static std::vector<std::string> split_lines(std::istream& is)`: Splits input stream into lines.
     - `template <typename T> InputHandler& operator<<(const T& value)`: Overloads insertion operator to handle input buffering.

3. **ConsoleInputHandler (Derived Class from InputHandler)**
   - **Purpose**: Handles console-based user input.
   - **Methods**:
     - `std::istream& get_user_input() override`: Gets userinput from the console.
     - `std::vector<std::string> get_instructions() override`: Reads instructions from a file.

4. **QtInputHandler (Derived Class from InputHandler)**
   - **Purpose**: Handles Qt-based user input.
   - **Methods**:
     - `std::istream& get_user_input() override`: Gets input from the Qt interface.
     - `std::vector<std::string> get_instructions() override`: Reads instructions from a Qt interface.
     - `void set_input_data(const std::string& data)`: Sets the input data.
     - `void set_instr_data(const std::vector<std::string>& data)`: Set the instruction data.
     - `void tie_input_ui(InputDialog& input_ui)`: Tis the input handler to the input UI.

5. **OutputHandler (Abstract Class)**
   - **Purpose**: Abstract base class for handling output.
   - **Methods**:
     - `virtual void handle_output() = 0`: Pure virtual method to handle output.
     - `std::ostream& pass_buffer()`: Passes the buffer for output.
     - `template <typename T> OutputHandler& operator<<(const T& value)`: Overloads insertion operator to handle output buffering.
     - `OutputHandler& operator<<(std::ostream& (*manip)(std::ostream&))`: Handles stream manipulators.

6. **ConsoleOutputHandler (Derived Class from OutputHandler)**
   - **Purpose**: Handles console-based output.
   - **Methods**:
     - `void handle_output() override`: Outputs buffered content to the console.

7. **QtOutputHandler (Derived Class from OutputHandler)**
   - **Purpose**: Handles output for a Qt-based interface.
   - **Methods**:
     - `void handle_output() override`: Outputs buffered content to a Qt interface.
     - `QtOutputHandler(std::function<void(const std::string&)> console)`: Constructor.

8. **Arithmetic Operations (Standalone Functions)**
   - **Purpose**: Provides arithmetic operations. 
   - **Functions**:
     - `void divide(short& accumulator, short* main_memory, short mem_addr)`: Divides the value in memory by the accumulator.
     - `void multiply(short& accumulator, short* main_memory, short mem_addr)`: Multiplies the value in memory with the accumulator.
     - `void add(short& accumulator, short* main_memory, short mem_addr)`: Adds the value in memory to the accumulator.
     - `void subtract(short& accumulator, short* main_memory, short mem_addr)`: Subtracts the value in memory from the accumulator.
     - `void checkOverflow(short& accumulator)`: Checks for overflow in the accumulator.

9. **Control Operations (Standalone Functions)**
   - **Purpose**: Provides control operations for branching and halting.
   - **Functions**:
     - `short halt()`: Halts the  execution.
     - `short branchNeg(short& accumulator, short cur_addr, short br_target)`: Branches if the accumulator is negative.
     - `short branchZero(short& accumulator, short cur_addr, short br_target)`: Branches if the accumulator is zero.
     - `short branch(short br_target)`: Branches unconditionally.

10. **Memory Operations (Standalone Functions)**
    - **Purpose**: Provides memory operations for loading and storing data.
    - **Functions**:
      - `void load(short& accumulator, short* main_memory, short mem_addr)`: Loads a value from memory into the accumulator.
      - `void store(short& accumulator, short* main_memory, short mem_addr)`: Stores the accumulator value into memory.

11. **IO Operations (Standalone Functions)**
    - **Purpose**: Provides input/output operations for reading and writing data.
    - **Functions**:
      - `template <size_t SIZE> void read(std::istream& is, short (&main_memory)[SIZE], short mem_addr)`: Reads a value into memory.
      - `template <size_t SIZE> void write(std::ostream& os, short (&main_memory)[SIZE], short mem_addr)`: Writes a value from memory to output.
      - `template <size_t SIZE> void write(OutputHandler& os, short (&main_memory)[SIZE], short mem_addr)`: Writes a value from memory to an output handler.

12. **InputDialog**
    - **Purpose**: Provides a dialog for user input in the Qt-based GUI.
    - **Functions**:
      - `explicit InputDialog(QWidget *parent= nullptr)`: Constructor to initialize the dialog.
      - `~InputDialog()`: Destructor to clean up the dialog.
      - `void on_submitButton_clicked()`: Slot to handle the submit button click event.

13. **MainWindow**
    - **Purpose**: Provides the main window for the Qt-based GUI, including handling user input and interaction with UVSim.
    - **Functions**:
      - `MainWindow(QWidget *parent = nullptr)`: Constructor to initialize the main window.
      - `~MainWindow()`: Destructor to clean up the main window.
      - `void write_to_console(const  std::string &str)`: Writes a string to the console.
      - `void write_to_console(const QString &outputString)`: Writes a QString to the console.
      - `void write_to_console(const char *cstr)`: Writes a C-string to the console.
      - `void overwrite_console(const std::string &str)`: Overwrites the console with a string.
      - `void overwrite_console(const QString &outputString)`: Overwrites the console with a QString.
      - `void overwrite_console(const char *cstr)`: Overwrites the console with a C-string.
      - `void handle_importButton_clicked()`: Handles the import button click event.
      - `void handle_runButton_clicked()`: Handles the run button click event.
      - `void on_inputReceived(const QString &input)`: Slot to handle received input from the input dialog.
      - `std::string get_user_input()`: Retrieves user input.

### Descriptions for Each Class and Function

1. **UVSim**
   - **Purpose**: This class represents the virtual machine simulator.
   - **Functions**:
     - `reset_memory()`: Resets all memory locations and the accumulator to zero
       - **Input Parameters**: None. 
       - **Return Value**:  None.
       - **Pre-Conditions**: None. 
       - **Post-Conditions**: All memory and accumulator are reset to zero.
     - `execute()`: Executes the instructions loaded in memory.
       - **Input Parameters**: None.
       - **Return Value**: None.
       - **Pre-Conditions**: Instructions must be loaded in memory.
       - **Post-Conditions**: Instructions are executed sequentially.
     - `split_instr(short instr, short* op_code, short* mem_addr)`: Splits an instruction into an opcode and a memory address.
       - **Input Parameters**: `instr` (instruction to split), `op_code` (pointer to store opcode), `mem_addr` (pointer to store memory address).
       - **Return Value**: None.
       - **Pre-Conditions**: `instr` must be a valid instruction.
       - **Post-Conditions**: `op_code` and `mem_addr` are populated.
     - `parse_input(std::vector<std::string>& lines)`: Parses input lines into memory.
       - **Input Parameters**: `lines` (vector of input lines).
       - **Return Value**: None.
       - **Pre-Conditions**: `lines` must be valid machine instructions.
       - **Post-Conditions**: Memory is populated with instructions
     - `execute_op(short op_code, short mem_addr, short cur)`: Executes a single operation based on the opcode
       - **Input Parameters**: `op_code` (operation code), `mem_addr` (memory address), `cur` (current instruction address)
       - **Return Value**: Next instruction address
       - **Pre-Conditions**: `op_code` must be a valid opcode
       - **Post-Conditions**: Operation is executed, and the next instruction address is returned
     - `get_accumulator()`: Returns the current value of the accumulator.
       - **Input Parameters**: None.
       - **Return Value**: Reference to the accumulator.
       - **Pre-Conditions**: None.
       - **Post-Conditions**: Accumulator value is accessible.
     - `get_memory()`: Returns the memory array.
       - **Input Parameters**: None.
       - **Return Value**: Pointer to the memory array.
       - **Pre-Conditions**: None.
       - **Post-Conditions**: Memory array is accessible.
     - `get_memory_value(short mem_addr)`: Returns the value at a specific memory address.
       - **Input Parameters**: `mem_addr` (memory address).
       - **Return Value**: Value at the specified memory address.
       - **Pre-Conditions**: `mem_addr` must be a valid address.
       - **Post-Conditions**: Value at `mem_addr` is returned
     - `set_accumulator(short value)`: Sets the accumulator to a specific value.
       - **Input Parameters**: `value` (value to set).
       - **Return Value**: None.
       - **Pre-Conditions**: None.
       - **Post-Conditions**: Accumulator is set to `value`.
     - `set_memory_address(short mem_addr, short value)`: Sets a specific memory address to a value.
       - **Input Parameters**: `mem_addr` (memory address), `value` (value to set).
       - **Return Value**: None.
       - **Pre-Conditions**: `mem_addr` must be a valid address.
       - **Post-Conditions**: Memory at `mem_addr` is set to `value`.
     - `run()`: Runs the virtual machine.
       - **Input Parameters**: None.
       - **Return Value**: None.
       - **Pre-Conditions**: Instructions must be loaded in memory.
       - **Post-Conditions**: Virtual machine executes the instructions.
     - `UVSim(InputHandler* handler_in, OutputHandler* handler_out)`: Constructor that initializes the UVSim with input and output handlers.
       - **Input Parameters**: `handler_in` (input handler), `handler_out` (output handler).
       - **Return Value**: None.
       - **Pre-Conditions**: None.
       - **Post-Conditions**: UVSim is initialized with handlers.
  
2. **InputHandler**
   - **Purpose**: Abstract class for handling user input.
   - **Functions**:
     - `virtual std::istream& get_user_input() = 0`: Pure virtual method to get user input.
       - **Input Parameters**: None.
       - **Return Value**: Input stream reference.
       - **Pre-Conditions**: Must be implemented by a derived class
       - **Post-Conditions**: Input stream is provided.
     - `virtual std::vector<std::string> get_instructions() = 0`: Pure virtual method to get instructions
       - **Input Parameters**: None.
       - **Return Value**: Vector of instructions.
       - **Pre-Conditions**: Must be implemented by a derived class.
       - **Post-Conditions**: Instructions are provided.
     - `static std::vector<std::string> split_lines(std::istream& is)`: Splits input stream into lines.
       - **Input Parameters**: `is` (input stream).
       - **Return Value**: Vector of lines.
       - **Pre-Conditions**: `is` must be a valid input stream.
       - **Post-Conditions**: Input stream is split into lines.
     - `template <typename T> InputHandler& operator<<(const T& value)`: Overloads insertion operator to handle input buffering.
       - **Input Parameters**: `value` (value to insert).
       - **Return Value**: Reference to the InputHandler.
       - **Pre-Conditions**: None.
       - **Post-Conditions**: Value is buffered.

3. **ConsoleInputHandler**
   - **Purpose**: Handles console-based user input.
   - **Functions**:
     - `std::istream& get_user_input() override`: Gets input from the console.
       - **Input Parameters**: None.
       - **Return Value**: Input stream reference.
       - **Pre-Conditions**: None
       - **Post-Conditions**: Input stream from the console is provided.
     - `std::vector<std::string> get_instructions() override`: Reads instructions from a file.
       - **Input Parameters**: None
       - **Return Value**: Vector of instructions.
       - **Pre-Conditions**: File must exist and be readable.
       - **Post-Conditions**: Instructions are read from the file

4. **QtInputHandler (Derived Class from InputHandler)**
   - **Purpose**: Handles Qt-based user input.
   - **Methods**:
     - `std::istream& get_user_input() override`: Gets input from the Qt interface.
     - `std::vector<std::string> get_instructions() override`: Reads instructions from a Qt interface.
     - `void set_input_data(const std::string& data)`: Sets the input data.
     - `void set_instr_data(const std::vector<std::string>& data)`: Sets the instruction data.
     - `void tie_input_ui(InputDialog& input_ui)`: Ties the input handler to the input UI.

5. **OutputHandler** 
   - **Purpose**: Abstract class for handling output.
   - **Functions**:
     - `virtual void handle_output() = 0`: Pure virtual method to handle output.
       - **Input Parameters**: None.
       - **Return Value**: None.
       - **Pre-Conditions**: Must be implemented by a derived class.
       - **Post-Conditions**: Output is handled.
     - `std::ostream& pass_buffer()`: Passes the buffer for output.
       - **Input Parameters**: None
       - **Return Value**: Output stream reference
       - **Pre-Conditions**: None.
       - **Post-Conditions**: Buffer is passed for output.
     - `template <typename T> OutputHandler& operator<<(const T& value)`: Overloads insertion operator to handle output buffering.
       - **Input Parameters**: `value` (value to insert).
       - **Return Value**: Reference to the OutputHandler
       - **Pre-Conditions**: None.
       - **Post-Conditions**: Value is buffered.
     - `OutputHandler& operator<<(std::ostream& (*manip)(std::ostream&))`: Handles stream manipulators.
       - **Input Parameters**: `manip` (manipulator function).
       - **Return Value**: Reference to the OutputHandler.
       - **Pre-Conditions**: None.
       - **Post-Conditions**: Manipulator is applied

6. **ConsoleOutputHandler**
   - **Purpose**: Handles console-based output.
   - **Functions**:
     - `void handle_output() override`: Outputs buffered content to the console.
       - **Input Parameters**: None.
       - **Return Value**: None.
       - **Pre-Conditions**: Buffer must contain output.
       - **Post-Conditions**: Buffer is output to the console.

7. **QtOutputHandler** 
   - **Purpose**: Handles output for a Qt-based interface.
   - **Functions**:
     - `void handle_output() override`: Outputs buffered content to a Qt interface.
       - **Input Parameters**: None.
       - **Return Value**: None.
       - **Pre-Conditions**: Buffer must contain output.
       - **Post-Conditions**: Buffer is output to the Qt interface.
     - `QtOutputHandler(std::function<void(const std::string&)> console)`: Constructor.
       - **Input Parameters**: `console` (function to handle Qt console output).
       - **Return Value**: None.
       - **Pre-Conditions**: None.
       - **Post-Conditions**: QtOutputHandler is initialized.

8. **Arithmetic Operations** 
   - **Purpose**: Provides arithmetic operations. 
   - **Functions**:
     - `void divide(short& accumulator, short* main_memory, short mem_addr)`: Divides the value in memory by the accumulator.
       - **Input Parameters**: `accumulator` (accumulator register), `main_memory` (memory array), `mem_addr` (memory address).
       - **Return Value**: None. 
       - **Pre-Conditions**: `mem_addr` must be valid, memory at `mem_addr` must not be zero
       - **Post-Conditions**: Accumulator contains the division result.
     - `void multiply(short& accumulator, short* main_memory, short mem_addr)`: Multiplies the value in memory with the accumulator.
       - **Input Parameters**: `accumulator` (accumulator register), `main_memory` (memory array), `mem_addr` (memory address)
       - **Return Value**: None
       - **Pre-Conditions**: `mem_addr` must be valid
       - **Post-Conditions**: Accumulator contains the multiplication result.
     - `void add(short& accumulator, short* main_memory, short mem_addr)`: Adds the value in memory to the accumulator.
       - **Input Parameters**: `accumulator` (accumulator register), `main_memory` (memory array), `mem_addr` (memory address).
       - **Return Value**: None.
       - **Pre-Conditions**: `mem_addr` must be  valid.
       - **Post-Conditions**: Accumulator contains the addition result.
     - `void subtract(short& accumulator, short* main_memory, short mem_addr)`: Subtracts the value in memory from the accumulator.
       - **Input Parameters**: `accumulator` (accumulator register), `main_memory` (memory array), `mem_addr` (memory address).
       - **Return Value**: None. 
       - **Pre-Conditions**: `mem_addr` must be valid. 
       - **Post-Conditions**: Accumulator contains the subtraction result.
     - `void checkOverflow(short& accumulator)`: Checks for overflow in the accumulator.
       - **Input Parameters**: `accumulator` (accumulator register).
       - **Return Value**: None.\
       - **Pre-Conditions**: Accumulator must have a valid value.
       - **Post-Conditions**: Overflow is checked and adjusted if necessary.

9. **Control Operations**
   - **Purpose**: Provides control  operations for branching and halting.
   - **Functions**:
     - `short halt()`: Halts the execution.
       - **Input Parameters**:  None.
       - **Return Value**: Special value indicating halt.
       - **Pre-Conditions**: None.
       - **Post-Conditions**: Execution is halted.
     - `short branchNeg(short& accumulator, short cur_addr, short br_target)`: Branches if the accumulator is negative.
       - **Input Parameters**: `accumulato r` (accumulator register), `cur_addr` (current address), `br_target` (branch target).
       - **Return Value**: Next address.
       - **Pre-Conditions**: `br_target` must be valid  
       - **Post-Conditions**: Branching is performed if accumulator is negative. 
     - `short branchZero(short& accumulator, short cur_addr, short br_target)`: Branches if the accumulator is zero.
       - **Input Parameters**: `accumulator` (accumulator register), `cur_addr` (current address), `br_target` (branch target).
       - **Return Value**: Next address.
       - **Pre-Conditions**: `br_target`  must be valid.  
       - **Post-Conditions**: Branching is performed if accumulator is zero.
     - `short branch(short br_target)`: Branches unconditionally
       - **Input Parameters**: `br_target` (branch target).
       - **Return Value**: Next address.
       - **Pre-Conditions**: `br_target` must be valid.
       - **Post-Conditions**: Branching is performed unconditionally

10. **Memory Operations**
    - **Purpose**: Provides memory operations for loading and storing data.
    - **Functions**:
      - `void load(short& accumulator, short* main_memory, short mem_addr)`: Loads a value from memory into the accumulator.
        - **Input Parameters**: `accumulator ` (accumulator register), `main_memory` (memory array), `mem_addr` (memory address).
        - **Return Value**: None.
        - **Pre-Conditions**: `mem_addr` must be valid
        - **Post-Conditions**: Accumulator contains the loaded value
      - `void store(short& accumulator, short* main_memory, short mem_addr)`: Stores the accumulator value into memory.
        - **Input Parameters**: `accumulator` (accumulator register), `main_memory` (memory array), `mem_addr` (memory address).
        - **Return Value**: None
        - **Pre-Conditions**: `mem_addr` must be valid
        - **Post-Conditions**: Memory at `mem_addr` contains the stored value

11. **IO Operations**
    - **Purpose**: Provides input/output operations for reading and writing data.
    - **Functions**:
      - `template <size_t SIZE> void read(std::istream& is, short (&main_memory)[SIZE], short mem_addr)`: Reads a value into memory.
        - **Input Parameters**:  `is ` (inputstream), `main_memory` (memory array), `mem_addr` (memory address).
        - **Return Value**: None.
        - **Pre-Conditions**: `mem_addr` must be valid.
        - **Post-Conditions**: Memory at `mem_addr` contains the read value.
      - `template <size_t SIZE> void write(std::ostream& os, short (&main_memory)[SIZE], short mem_addr)`: Writes a value from memory to output.
        - **Input Parameters**: `os` (output stream), `main_memory` (memory array), `mem_addr` (memory address).
        - **Return Value**: None.
        - **Pre-Conditions**:  `mem_addr` must be valid
        - **Post-Conditions**: Output contains the value from memory
      - `template <size_t SIZE> void write(OutputHandler& os, short (&main_memory)[SIZE], short mem_addr)`: Writes a value from memory to an output handler.
        - **Input Parameters**: `os` (output handler), `main_memory` (memory array), `mem_addr` (memory address)
        - **Return Value**: None.
        - **Pre-Conditions**: `mem_addr` must be valid.
        - **Post-Conditions**: Output handler contains the value from memory.

12. **InputDialog**
    - **Purpose**: Provides a dialog for user input in the Qt-based GUI.
    - **Attributes**:
        - `Ui::InputDialog *ui`: Pointer to the UI elements of the dialog.
    - **Methods**:
        - `explicit InputDialog(QWidget *parent = nullptr)`: Constructor to initialize the dialog.
          - **Input Parameters**: `parent` (optional QWidget parent).
          - **Return Value**: None.
          - **Pre-Conditions**: None.
          - **Post-Conditions**: Dialog is initialized.
        - `~InputDialog()`: Destructor to clean up the dialog.
          - **Input Parameters**: None.
          - **Return Value**: None.
          - **Pre-Conditions**: None.
          - **Post-Conditions**: UI elements are deleted.
        - `void on_submitButton_clicked()`: Slot to handle the submit button click event.
          - **Input Parameters**: None.
          - **Return Value**: None.
          - **Pre-Conditions**:None.
          - **Post-Conditions**:  Input is submitted and dialog is closed.
    - **Signals**:
        - `void inputSubmitted(const QString &input)`: Signal emitted when input is submitted.
          - **Input Parameters**: `input` (submitted input as a QString).
          - **Return Value**: None.
          - **Pre-Conditions**: None.
          - **Post-Conditions**: Input is emitted.

13. **MainWindow**
    - **Purpose**: Provides the main window for the Qt-based GUI, including handling user input and interaction with UVSim.
    - **Attributes**:
        - `Ui::MainWindow *ui`: Pointer to the UI elements of the main window.
        - `InputDialog *userInput`: Pointer to the input dialog.
        - `std::vector<std::string> importData`: Vector to store imported data.
        - `QtInputHandler input_handler`: Input handler for  Qt-based input
        - `QtOutputHandler  output_handler`: Output handler for Qt-based output
        - `UVSim uv_sim`: Instance of the UVSim simulator.
    - **Methods**:
        - `MainWindow(QWidget *parent = nullptr)`: Constructor to initialize the main window.
          - **Input Parameters**: `parent` (optional QWidget parent).
          - **Return Value**: None.
          - **Pre-Conditions**: None.
          - **Post-Conditions**: Main window is initialized.
        - `~MainWindow()`: Destructor to clean up the main window.
          - **Input Parameters**: None.
          - **Return Value**: None.
          - **Pre-Conditions**:  None.
          - **Post-Conditions**:UI elements are deleted.
        - `void write_to_console(const  std::string &str)`:Writes a string to the console.
          - **Input Parameters**: `str`(string to write).
          - **Return Value**: None
          - **Pre-Conditions**:  None
          - **Post-Conditions**: String is written to the console.
        - `void write_to_console(const QString &outputString)`: Writes a QString to the console.
          - **Input Parameters**: `outputString` (QString to write).
          - **Return Value**: None
          - **Pre-Conditions**: None
          - **Post-Conditions**: QString is written to the console.
        - `void write_to_console(const char *cstr)`: Writes a C-string to the console
          - **Input Parameters**: `cstr` (C-string to write).
          - **Return Value**: None.
          - **Pre-Conditions**: None
          - **Post-Conditions**: C-string is written to the console
        - `void overwrite_console(const std::string &str)`: Overwrites the console with a string.
          - **Input Parameters**: `str` (string to write).
          - **Return Value**:None.
          - **Pre-Conditions**: None
          - **Post-Conditions**: Console is overwritten with the string.
        - `void overwrite_console(const QString &outputString)`: Overwrites the console with a QString.
          - **Input Parameters**: `outputString` (QString to write).
          - **Return Value**:  None
          - **Pre-Conditions**: None
          - **Post-Conditions**: Console is overwritten with the QString.
        - `void overwrite_console(const char *cstr)`: Overwrites the console with a C-string.
          - **Input Parameters**: `cstr` (C-string to write).
          - **Return Value**: None.
          - **Pre-Conditions**: NA
          - **Post-Conditions**: Console is overwritten with the C-string.
        - `void handle_importButton_clicked()`: Handles the import button click event.
          - **Input Parameters**: None.
          - **Return Value**: None.
          - **Pre-Conditions**:NA
          - **Post-Conditions**: File is imported and processed.
        - `void handle_runButton_clicked()`: Handles the run button click event.
          - **Input Parameters**: None.
          - **Return Value**: None.
          - **Pre-Conditions**: Imported data must be available.
          - **Post-Conditions**: UVSim program is executed.
        - `void on_inputReceived(const QString &input)`: Slot to handle received input from the input dialog.
          - **Input Parameters**: `input` (received input as a QString).
          - **Return Value**: None
          - **Pre-Conditions**: None
          - **Post-Conditions**: Input is processed
        - `std::string get_user_input()`: Retrieves user input
          - **Input Parameters**: None
          - **Return Value**: User input as a string
          - **Pre-Conditions**: None  
          - **Post-Conditions**: User input is retrieved.
  