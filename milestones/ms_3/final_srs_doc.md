# Software Requirement Specification

## Functional Requirements
1. The system shall have and manage 100 memory addresses, with each address representing a word (signed four-digit decimal number).
2. The system shall execute instructions sequentially based off their OP CODE.
3. The system shall detect and handle arithmetic operation overflow 
4. The system shall load BasicML programs starting at a predefined location in memory
5. The system shall handle errors without crashing
6. The system shall handle reading invalid values
7. The system shall provide an operation that stores input from the user into memory
8. The system shall provide an operation that will output a word from memory.
9. The system shall provide an operation that loads a value from memory into the accumulator
10. The system shall provide an operation that stores a value from the accumulator into memory
11. The system shall provide an operation that adds a value from memory to the accumulator
12. The system shall provide an operation that subtracts a value in memory from the accumulator 
13. The system shall provide an operation that divides the value in the accumulator by a value from memory
14. The system shall provide an operation that multiplies the value in the accumulator by a value from memory
15. The system shall provide an operation that branches to a specified memory location 
16. The system shall provide an operation that branches to a specified memory location if the accumulator is negative 
17. The system shall provide an operation that branches to a specified memory location if the accumulator is zero
18. The system shall provide an operation that stops the execution of the program 
19. The system shall provide a way to collect user input and display output

## Non-functional Requirements
1. The system shall help users to learn a simplified machine language
2. The system shall execute each instruction within 1 second under normal operational conditions
3. The system shall have a user interface that clearly distinguishes each field and its functionality