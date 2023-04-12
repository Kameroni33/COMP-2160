# COMP 2160 - Assignment 4

Kameron Ronald  
ronaldk1@myumanitoba.ca  
7880495  

## Compiling & Running

```shell
make        # compiles executables for main-test and main
make dev    # compiles executable for main-test
make prod   # compiles executable for main
make clean  # removes all executable files

./main-test  # run basic testing with ASSERT statements
./main       # run basic testing without ASSERT statements
```

For my ObjectManager implementation, it takes the approach of flagging data as 'deleted' but not actually overwritting the data to ensure it is physically destroyed (similar to a typical implementation of malloc). Thus, unless overwritten, old data may still be found stored in the buffer space. Similarly, when new memory is allocated in the buffer space, there is no gaurantee as to its inital value. It is up to the user to write data to this memory; a pre-emptive read my result in stale or unexpected values. Operations to ensure data deletion and initialization could easily be implemented by writting 0's to the buffer space when allocated and deleted, but seemed outside the scope of this assignments objectives.

The `main.c` file has been included with some tests for ObjectManager.c. It can be compiled with ASSERT statements (`main-test`) or without ASSERT statements (`main`). The test file is designed to just go through basic usage of ObjectManager.c (and some edge cases), printing information and verifing values as it goes. Largely is it up the a user to verify the tests have passed, as a white-box approach to testing would require exposing a number of implementation specific details. It tests creating, adding, removing, and compacting various sized objects. Additionally, it tests a number of the 'invalid' or failure cases for ObjectManager.c. Errors from ObjectManager.c are printed to STDERR while regular information is printed to STDOUT.
  