# SET Calculator README

## Introduction
This program is a SET calculator designed to perform various operations on sets. Sets, named SETA to SETF, can hold numbers between 0 and 127. Operations include reading numbers into sets, printing sets, performing union, intersection, subtraction, and symmetric difference operations between sets. 

## Usage
1. **Compilation**: Compile the program using the provided Makefile.
    ```bash
    make
    ```
    This will generate an executable named `a.out`.

2. **Execution**: Run the program by executing the generated executable.
    ```bash
    ./a.out
    ```
    This will start the SET calculator.

3. **Commands**:
    - **read_set**: <br>
    \tRead numbers into a particular set. Numbers must be positive integers, separated by commas, and terminated with -1. Example: `read_set SETA, 3, 1, 22, -1`.
    - **print_set**: <br>
    \tPrint all numbers inserted into a specified set. Example: `print_set SETB`.
    - **union_set**: <br>
    \tPerform the union operation between three sets. Example: `union_set SETA, SETB, SETC`.
    - **sub_set**: <br>
    \tPerform the subtraction operation between three sets. Example: `sub_set SETA, SETB, SETC`.
    - **intersect_set**: <br>
    \tPerform the intersection operation between three sets. Example: `intersect_set SETA, SETB, SETC`.
    - **symdiff_set**: <br>
    \tPerform the symmetric difference operation between three sets. Example: `symdiff_set SETA, SETB, SETC`.
    - **stop**: <br>
    \tTerminate the calculator.

4. **Notes**: <br>
    - The calculator allows whitespace between commands and parameters but does not allow additional text or commas.
    - Numbers must be integers between 0 and 127.
    - Each command must be followed by the appropriate set names separated by commas.

5. **Cleanup**: To clean up object files and the executable, run:
    ```bash
    make clean
    ```
    
![Local Image](/tests/example_1.png)

- **License**: MIT License

