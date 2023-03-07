# COMP 2160 - Assignment 2

Kameron Ronald  
7880495  
ronaldk1@myumanitoba.ca

## Compiling & Running

For convience I've included a Makefile. *maze_start.c* is compiled as *maze*.

```shell
make              # compiled with flags: -Wall 
make development  # compiled with flags: -Wall -Wextra -Wpedantic -Werror -g
make production   # compiled with flags: -Wall -DNDEBUG
make clean        # removes compiled builds

# run the program with input file "testmaze.txt"
./maze < testmaze.txt
```
