# Set Calculator
Welcome to the Set Calculator! This calculator allows you to manipulate up to seven different sets, 
from 'SETA' to 'SETF', by filling them with numbers between 0 and 127. 

Here's what you need to know to use the Set Calculator:

## Usage

- The calculator can be stopped immediately by using the stop action or by pressing the EOF key combination.
- You can use the read_set action to read numbers into a particular set group. Numbers must be positive and at the end of the read action, you should include the number -1. Each number should be separated by a comma. For example, read_set SETA, 3, 1, 22, -1.
- You can use the print_set action followed by the set name to print all numbers inserted into the group. The output will display up to sixteen numbers per line.
- You can perform group manipulation using the following actions:
  - union_set: union of three set groups.
  - sub_set: subtraction of two set groups.
  - intersect_set: intersection of three set groups.
  - symdiff_set: symmetrical difference of three set groups.
  Each action must be followed by three set-groups separated by a comma.

## Usage Notes
- By pressing the enter key, you can enter orders one after another in the calculator.
- You can use whitespace as you wish. However, additional text or commas are not allowed.

## Have fun and good luck!

