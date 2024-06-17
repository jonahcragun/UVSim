# Software Requirement Specification - Group 2 (Jaykant & Zac)

## Working Draft 1 - Jonah

## Functional Requirements
1. The system shall prompt the user to upload a file
2. The system shall load the fine into the memory array
3. The system shall display an error message if an invalid op code is read
4. The system shall display an error message if the file entered has too many lines
5. The system shall display an error message if there is an overflow
6. The system shall perform the an operation based on which opcode is read
7. The system shall display a text window that that gets user info 
8. The system shall display a terminal window that prints system output
9. The system shall display a box to represent each position in memory
10. The System shall display the value associated with each memory position in a box next to it
11. The system shall have an op code that adds a number with the accumulator and stores it in memory
12. The system shall have an op code that outputs to the console
13. The system shall have an op code that gets input from the console
14. The system shall have an op code that branches to a different location in memory
15. The system shall have an op code that loads a value from memory into the accumulator

## Non-functional Requirements
1. The system shall be user friendly
2. The system shall help users to learn a simplified machine language
3. The system shall be a teaching tool for computer science students

## Working Draft 2 - Andrew

## Functional
1. The system shall be able to add a number from memory to a number in the accumulator
2. The system shall be able to subtract a number in memory from the number in the accumulator.
3. The system shall be able to divide the number in the accumulator by a number in memory
4. The system shall be able to multiple the number in the accumulator by a number in memory
5. The system shall be able to change the current instruction pointer
6. The system shall be able to change the current instruction pointer if the accumulator is zero.
7. The system shall be able to change the current instruction pointer if the accumulator is negative.
8. The system shall be able to take in a 4 digit number with an optional sign as an input and store it in memory
9. The system shall be able to output a 4 digit number from memory.
10. The system shall be able to store the value in the accumulator into memory.
11. The system shall be able to load a number from memory into the accumulator.
12. The system shall be able to ask the user to choose a file
13. The system shall be able to read in a file of machine language instructions
14. The system shall be able to split instructions into their associated OP CODE and memory address.
15. The system shall be able to run instructions based off of their OP CODE.

## Non-Functional
1. The system will read each line in the user provided file and validate that it is in machine language format
2. The system shall provide an input text field for the user to enter op codes or file names.
3. The system shall output all outputs to the GUI Console.