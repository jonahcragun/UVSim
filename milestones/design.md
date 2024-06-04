# UVSim Overview

## Introduction
UVSim is a simple virtual machine simulator that allows students to load, execute, and debug machine language programs. 
It provides a controlled environment for understanding CPU operations, register manipulations, and memory interactions. 
UVSim is designed to be user-friendly and educational, making it an ideal tool for computer science students and instructors.

## User Stories
### User Story 1
- As a student, I want to execute machine language programs so that I can learn the language BasicML.

### User Story 2
- As a educational company, I want have good learning tools so that our students can be taught effectively.

## Use Cases
### Use Case 1
- **ACTOR**: ADD algorithm


- **SYSTEM**: Arithmetic System


- **GOAL**: Add the number from the instructions provided memory address to the number that is currently in the accumulator


- **STEPS**:
1. Get number in provided memory address
2. Add the number to the number in the accumulator

### Use Case 2
- **ACTOR**: SUBTRACT algorithm


- **SYSTEM**: Arithmetic System


- **GOAL**: Subtract the number in the provided memory address from the number in the accumulator.


- **STEPS**:
1. Get number in provided memory address
2. Subtract the number from the number in the accumulator
 

### Use Case 3
- **ACTOR**: BRANCH algorithm


- **SYSTEM**: Control System


- **GOAL**: Branch to the instruction at the provided memory location


- **STEPS**:
1. Set the current pointer equal to the provided memory address.

### Use Case 4
- **ACTOR**: Branch Negative 


- **SYSTEM**: Control System


- **GOAL**: Branch to the instruction at the provided memory location if the accumulator is negative.


- **STEPS**:
1. Check if the provided memory address (br_target) is within the valid range.
2. If the accumulator is negative, set the current pointer to the provided memory address.
3. If the accumulator is not negative, increment the current memory address and set it as the current pointer.

### Use Case 5
- **ACTOR**: Branch Zero 


- **SYSTEM**: Control System


- **GOAL**: Branch to the instruction at the provided memory location if the accumulator is zero.


- **STEPS**:
1. Check if the provided memory address (br_target) is within the valid range.
2. If the accumulator is zero, set the current pointer to the provided memory address.
3. If the accumulator is not zero, increment the current memory address and set it as the current pointer.

### Use Case 6
- **ACTOR**: Store Algorithm


- **SYSTEM**: Memory Management System


- **GOAL**: Store the value in the accumulator to a specific memory location.


- **STEPS**:
1. Check if the provided memory address (mem_addr) is within the valid range.
2. Store the value in the accumulator at the specified memory address.

### Use Case 7
- **ACTOR**: Read Algorithm


- **SYSTEM**: I/O System


- **GOAL**: read in a value from the terminal into a specified location in memory.


- **STEPS**:
1. Check that memory location is within a valid range.
2. Wait for user input.
3. Store value into specifed memory location after the enter key has been read.

### Use Case 8
- **ACTOR**: Write Algorithm


- **SYSTEM**: I/O System


- **GOAL**: Write value to the console from specified memory location. 


- **STEPS**:
1. Check that memory loaction is within a valid range.
2. Get value from specified memory address.
3. Write value to the terminal.

### Use Case 9
- **ACTOR**: Halt Algorithm


- **SYSTEM**: Control System


- **GOAL**: Stop the program from running.


- **STEPS**:
1. Return a value greater than the size of addressable memory.

### Use Case 10
- **ACTOR**: Load Algorithm


- **SYSTEM**: Memory Management System


- **GOAL**: Load the value from a specific memory location into the accumulator.


- **STEPS**:
1. Check if the provided memory address(mem_addr) is within the valid range.
2. Load the value from the specified memmory address into the accumulator
   

### Use Case 11
- **ACTOR**: Divide Algorithm


- **SYSTEM**: Arithmetic System


- **GOAL**: Divide the number in the accumulator by the number at the provided memory address.


- **STEPS**:
1. Get the number from the provided memory address.
2. If the number is zero, throw a division by zero error.
3. Divide the number in the accumulator by the number from the provided memory address.

### Use Case 12
- **ACTOR**: Multiply Algorithm


- **SYSTEM**: Arithmetic System


- **GOAL**: Multiply the number in the accumulator by the number at the provided memory address.


- **STEPS**:
1. Get the number from the provided memory address.
2. Multiply the number in the accumulator by the number from the provided memory address.


## Unit Tests Spreadsheet

| Test Name | Description                                  | Use Case Reference | Inputs | Expected Outputs           | Success Criteria                                                                         |
|-----------|----------------------------------------------|--------------------|--------|----------------------------|------------------------------------------------------------------------------------------|
| Test 1    | Tests addition operation                     | Use Case 1         | None   | Correct addition result    | Will correctly add the number from the provided memory address to the accumulator        |
| Test 2    | Tests out-of-range addition operation        | Use Case 2         | None   | Error thrown               | Will correctly throw an error when the memory address is out of range                    |
| Test 3    | Tests subtraction operation                  | Use Case 3         | None   | Correct subtraction result | Will correctly subtract the number from the provided memory address from the accumulator |
| Test 4    | Tests out-of-range subtraction operation     | Use Case 4         | None   | Error thrown               | Will correctly throw an error when the memory address is out of range                    |
| Test 5    | Tests branch operation                       | Use Case 5         | None   | Correct branch target      | Will correctly return the target memory address                                          |
| Test 6    | Tests out-of-range branch operation          | Use Case 6         | None   | Error thrown               | Will correctly throw an error when the memory address is out of range                    |
| Test 7    | Tests branch negative operation              | Use Case 7         | None   | Correct branch target      | Will correctly branch to the target memory address when accumulator is negative          |
| Test 8    | Tests out-of-range branch negative operation | Use Case 8         | None   | Error thrown               | Will correctly throw an error when the memory address is out of range                    |
| Test 9    | Tests branch zero operation                  | Use Case 9         | None   | Correct branch target      | Will correctly branch to the target memory address when accumulator is zero              |
| Test 10   | Tests out-of-range branch zero operation     | Use Case 10        | None   | Error thrown               | Will correctly throw an error when the memory address is out of range                    |
| Test 11   | Tests store operation                        | Use Case 11        | None   | Correct store result       | Will correctly store the accumulator value to the specified memory address               |
| Test 12   | Tests out-of-range store operation           | Use Case 12        | None   | Error thrown               | Will correctly throw an error when the memory address is out of range                    |
| Test 13   | Tests load operation                         | Use Case 13        | None   | Correct load result        | Will correctly load the value from the specified memory address into the accumulator    |
| Test 14   | Tests out-of-range load operation            | Use Case 14        | None   | Error thrown               | Will correctly throw an error when the memory address is out of range                |
| Test 15   | Tests divide operation                       | Use Case 15        | None   | Correct divide result      | Will correctly divide the accumulator by the value at the specified memory address     |
| Test 16   | Tests divide by zero operation               | Use Case 16        | None   | Error thrown               | Will correctly thrown an error when attempting to divide by zero                  |
| Test 17   | Tests multiply operation                     | Use Case 17        | None   | Correct multiply result    | Will correctly multiply the accumulator by the value at the specified memory address     |
| Test 18   | Tests out-of-range multiply operation        | Use Case 18        | None   | Error thrown               | Will correctly throw an error when the memory address is out of range                |
| Test 19   | Tests read operation                         | Use Case 7         | None   | Correct input result       | Will correctly read value from stream                                                    |
| Test 20   | Tests out-of-range read operation            | Use Case 7         | None   | Error Thrown               | Will throw error when index is out of range                                              |
| Test 21   | Tests write operation                        | Use Case 8         | None   | Correct output resutl      | Will correctly write value to stream                                                     |
| Test 22   | Tests out-of-range write operation           | Use Case 8         | None   | Error Thrown               | Will throw error when index is out of range                                              |
| Test 23   | Tests halt operation                         | Use Case 9         | None   | Correct returned result    | Will correctly return value larger than the size of the memory array to stop program     |
| Test 24   | Tests halt operation in execute\_op          | Use Case 9         | None   | Correct returned result    | Will correctly return value larger than the size of the memory array to stop program     |
