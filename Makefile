# Compiler and version
COMP = g++
VERSION = -std=c++2a

# Flags for creating object files
OBJFLAGS ?= -c

# Directories
OBJDIR = obj
#HEADERDIR = header
#SRCDIR = src

# Program Files
PROG_MAIN_OBJ = $(OBJDIR)/main.o

SRCS += \
    UVSim.cpp \
    input_handler.cpp \
    console_input.cpp \
    output_handler.cpp \
    console_output.cpp \
    arithmetic_op.cpp \
    control_op.cpp \
    memory_op.cpp
    
# Reference substitution: will place anything that % represents in SRCS:%.cpp to the % in $(OBJDIR)/%.o
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

# Test Framework files
TEST_SRCS = test.cpp
TEST_MAIN_OBJ = $(OBJDIR)/test.o
TEST_TARGET = test

# Target executable
TARGET = UVSim

all: $(TARGET)

$(TARGET): $(PROG_MAIN_OBJ) $(OBJS)
	$(COMP) $(VERSION) $(PROG_MAIN_OBJ) $(OBJS) -o $(TARGET)

# Ensure the object directory exists before compiling object files
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(COMP) $(VERSION) $(OBJFLAGS) $< -o $@

# Create the object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile source files into object files
main.o: main.cpp UVSim.h
	$(COMP) $(VERSION) $(OBJFLAGS) main.cpp

UVSim.o: UVSim.cpp UVSim.h constants.h io_op.h
	$(COMP) $(VERSION) $(OBJFLAGS) UVSim.cpp

input_handler.o: input_handler.cpp input_handler.h
	$(COMP) $(VERSION) $(OBJFLAGS) input_handler.cpp

console_input.o: console_input.cpp console_input.h
	$(COMP) $(VERSION) $(OBJFLAGS) console_input.cpp

qt_input.o: qt_input.cpp qt_input.h
	$(COMP) $(VERSION) $(OBJFLAGS) qt_input.cpp

output_handler.o: output_handler.cpp output_handler.h
	$(COMP) $(VERSION) $(OBJFLAGS) output_handler.cpp

console_output.o: console_output.cpp console_output.h
	$(COMP) $(VERSION) $(OBJFLAGS) console_output.cpp

qt_output.o: qt_output.cpp qt_output.h
	$(COMP) $(VERSION) $(OBJFLAGS) qt_output.cpp 

arithmetic_op.o: arithmetic_op.cpp arithmetic_op.h
	$(COMP) $(VERSION) $(OBJFLAGS) arithmetic_op.cpp

control_op.o: control_op.cpp control_op.h
	$(COMP) $(VERSION) $(OBJFLAGS) control_op.cpp

memory_op.o: memory_op.cpp memory_op.h
	$(COMP) $(VERSION) $(OBJFLAGS) memory_op.cpp

# Compile test files into object files
test.o: test.cpp test.h
	$(COMP) $(VERSION) $(OBJFLAGS) test.cpp -o $(OBJDIR)/test.o

test: $(TEST_MAIN_OBJ) $(OBJS)
	$(COMP) $(VERSION) $(TEST_MAIN_OBJ) $(OBJS) -o $(TEST_TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TEST_TARGET)