# UVSim Overview

## Introduction
UVSim is a simple virtual machine simulator that allows students to load, execute, and debug machine language programs. 
It provides a controlled environment for understanding CPU operations, register manipulations, and memory interactions. 
UVSim is designed to be user-friendly and educational, making it an ideal tool for computer science students and instructors.

## User Stories
### User Story 1
- As a ____, I want ____ so that ____.

### User Story 2
- As a ____, I want ____ so that ____.

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
- **ACTOR**: 


- **SYSTEM**: 


- **GOAL**: 


- **STEPS**:
1. 
2. 
3. 

### Use Case 8
- **ACTOR**: 


- **SYSTEM**: 


- **GOAL**: 


- **STEPS**:
1. 
2. 
3. 

### Use Case 9
- **ACTOR**: 


- **SYSTEM**: 


- **GOAL**: 


- **STEPS**:
1. 
2. 
3. 

### Use Case 10
- **ACTOR**: 


- **SYSTEM**: 


- **GOAL**: 


- **STEPS**:
1. 
2. 
3. 

### Use Case 11
- **ACTOR**: 


- **SYSTEM**: 


- **GOAL**: 


- **STEPS**:
1. 
2. 
3. 

### Use Case 12
- **ACTOR**: 


- **SYSTEM**: 


- **GOAL**: 


- **STEPS**:
1. 
2. 
3. 

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
| Test 13   | Tests ____                                   | Use Case 13        | None   | ____                       | ____                                                                                     |
| Test 14   | Tests ____                                   | Use Case 14        | None   | ____                       | ____                                                                                     |
| Test 15   | Tests ____                                   | Use Case 15        | None   | ____                       | ____                                                                                     |
| Test 16   | Tests ____                                   | Use Case 16        | None   | ____                       | ____                                                                                     |
| Test 17   | Tests ____                                   | Use Case 17        | None   | ____                       | ____                                                                                     |
| Test 18   | Tests ____                                   | Use Case 18        | None   | ____                       | ____                                                                                     |
| Test 19   | Tests ____                                   | Use Case 19        | None   | ____                       | ____                                                                                     |
| Test 20   | Tests ____                                   | Use Case 20        | None   | ____                       | ____                                                                                     |
| Test 21   | Tests ____                                   | Use Case 21        | None   | ____                       | ____                                                                                     |
| Test 22   | Tests ____                                   | Use Case 22        | None   | ____                       | ____                                                                                     |
| Test 23   | Tests ____                                   | Use Case 23        | None   | ____                       | ____                                                                                     |
| Test 24   | Tests ____                                   | Use Case 24        | None   | ____                       | ____                                                                                     |
