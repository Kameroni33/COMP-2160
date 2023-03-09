# COMP 2160 - Assignment 2

Kameron Ronald  
7880495  
ronaldk1@myumanitoba.ca

## Compiling & Running

For convience I've included a Makefile. *maze.c* is compiled as *maze*.

```shell
make              # compiled with flags: -Wall 
make development  # compiled with flags: -Wall -Wextra -Wpedantic -Werror -g
make production   # compiled with flags: -Wall -DNDEBUG
make clean        # removes compiled builds

# run the program with input file "testmaze.txt" (or whatever maze you want to)
./maze < testmaze.txt
```
