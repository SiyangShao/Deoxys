## Deoxys
The repository includes an implementation of Deoxys using Intel Intrinsics and performs encryption on a unit of 6 blocks.

## Contents
The repository includes the following files:

+ Deoxys.c: This file contains the main implementation of the Deoxys algorithm.
+ ref-input: This file represents the input test case
  + input: This file contains the input for the implementation. It has the same content as ref-input, but the format has been modified to enable reading with scanf.
+ ref-output: This file represents the output for the test case

## Execution
To build this implementation, execute the following commands in the terminal:
``` bash
make clean
make
```
Once the build is successful, you can test the implementation using the following command:
``` bash
make test
```
This command will run the implementation with the provided input and compare the output with the reference output. Any differences between the two outputs will be displayed.
