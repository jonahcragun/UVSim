# Software Requirement Specification - Group 2 (Andrew & Jonah)


## Working Draft 1 - Jaykant

## Functional Requirements
1. The system shall execute instructions sequentially from memory.
2. The system shall store the value from the accumulator’s value to the target memory address.
3. The system shall load the value from the specified memory address into the accumulator.
4. The system shall detect and handle arithmetic operation overflow, setting an overflow flag and truncating the result if specified.
5. The system shall handle errors gracefully and provide text error messages on console.
6. The system shall read instructions, and the user shall input a value stored in the provided memory.
7. The system shall perform the addition operation between the accumulator and a value from memory.
8. The system performs the subtraction operation between the accumulator and a value from memory.
9. The system shall perform the division operation between the accumulator and a value from memory.
10. The system shall perform the multiplication operation between the accumulator and a value from memory.
11. The system shall branch to specified memory address when a ‘Branch’ instruction is called.
12. The system shall branch to specified memory address if the accumulator is zero.
13. The system shall branch to specified memory address if the accumulator is positive.
14. The system shall display specified memory value on the console.
15. The system shall stop executing the program, or halt.

## Non-functional Requirements 
1. The system shall execute the program within a reasonable execution time.
2. The system shall have a reliable and user-friendly interface with GUI.
3. The system shall be maintainable and easy to fix bugs


## Working Draft 2 - Zac

## Functional Requirements
1. The system shall have and manage 100 memory addresses, with each address representing a signed four-digit decimal number
2. The system shall load BasicML programs into memory starting from a predefined location.
3. The system shall handle input operations that read a value from the keyboard into memory as specified by a READ instruction
4. The system shall handle output operations that write a value from memory to the screen as specified by a WRITE instruction
5. The system shall load a value from memory into the accumulator as specified by a LOAD instruction
6. The system shall store a value from the accumulator into memory as specified by a STORE instruction
7. The system shall add a value from memory to the accumulator as specified by an ADD instruction
8. The system shall subtract a value from memory from the accumulator as specified by a SUBTRACT instruction
9. The system shall divide the value in the accumulator by a value from memory as specified by a DIVIDE instruction
10. The system shall multiply a value from memory with the value in the accumulator as specified by a MULTIPLY instruction
11. The system shall perform a branch operation to a memory location as specified by a BRANCH instruction
12. The system shall perform a conditional branch to a memory location if the accumulator is negative as specified by a BRANCHNEG instruction
13. The system shall perform a conditional branch to a memory location if the accumulator is zero as specified by a BRANCHZERO instruction
14. The system shall stop the execution of the program when specified by a HALT instruction
15. The system shall provide a user interface for uploading instruction files
16. The system shall prompt the user for input when necessary.
17. The system shall display output to the user 

## Non-functional Requirements 
1. The system shall execute each instruction within a reasonable time frame under normal operational conditions
2. The system shall offer an intuitive user interface
3. The system shall provide clear guidance for users to load programs, enter inputs, and view outputs
4. The system shall provide clear error messages for invalid instructions or operations.
5. The system shall handle errors without crashing 