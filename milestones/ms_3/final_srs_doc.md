# Software Requirement Specification

## Functional Requirements
1.

## Non-functional Requirements
1. 

## Functional Requirements
1. The system shall have and manage 100 memory addresses, with each address representing a signed four-digit decimal number
2. The system shall execute instructions sequentially from memory when the program is run
3. The system shall detect and handle arithmetic operation overflow, setting an overflow flag and truncating the result if specified
4. The system shall load BasicML programs into memory starting from a predefined location
5. The system shall handle errors without crashing
6. The system shall provide an operation that reads a value from the keyboard into memory 
7. The system shall provide an operation that writes a value from memory to the screen 
8. The system shall provide an operation that loads a value from memory into the accumulator 
9. The system shall provide an operation that stores a value from the accumulator into memory 
10. The system shall provide an operation that adds a value from memory to the accumulator 
11. The system shall provide an operation that subtracts a value from memory from the accumulator 
12. The system shall provide an operation that divides the value in the accumulator by a value from memory 
13. The system shall provide an operation that multiplies the value in the accumulator with a value from memory 
14. The system shall provide an operation that branches to a specified memory location 
15. The system shall provide an operation that branches to a specified memory location if the accumulator is negative 
16. The system shall provide an operation that branches to a specified memory location if the accumulator is zero 
17. The system shall provide an operation that stops the execution of the program 
18. The system shall provide an user input field in the GUI
19. The system shall provide an console output field in the GUI
20. The system shall provide a field to load in the contents of a file in the GUI
21. The system shall provide a button to run the program loaded in memory in the GUI


## Non-functional Requirements
1. The system shall execute each instruction within 1 second under normal operational conditions
2. The system shall have an intuitive user interface that clearly distinguishes each field and its functionality
3. The system shall provide clear and concise error messages for invalid instructions or operations.


# Software Requirement Specification - Group 2 (Jaykant & Zac)

## Functional Requirements
1. The system shall be able to ask the user to choose a file.
2. The system shall be able to read in a file.
3. The system shall be able to run instructions based off of their OP CODE.
4. The system shall display an error message if an invalid op code is read.
5. The system shall be able to output a 4-digit number from memory.
6. The system shall be able to store a 4-digit number with an optional sign in memory.
7. The system shall be able to load a number from memory into the accumulator.
8. The system shall be able to add a number from memory to a number in the accumulator.
9. The system shall be able to subtract a number in memory from the number in the accumulator.
10. The system shall be able to multiply the number in the accumulator by a number in memory.
11. The system shall be able to divide the number in the accumulator by a number in memory.
12. The system shall have an op code that gets input from the console.
13. The system shall have an op code that branches to a different location in memory.
14. The system shall be able to change the current instruction pointer based on the value in the accumulator.
15. The system shall output all outputs to the GUI Console.

## Non-functional Requirements
1. The system shall be user friendly
2. The system shall help users to learn a simplified machine language
3. The system shall be a teaching tool for computer science students