# COMP 2160 - Assignment 3

Kameron Ronald  
ronaldk1@myumanitoba.ca  
7880495  

## Compiling & Running

A Makefile has been included for compiling files. Both question 1 and 2 compile with the "orderedList" library. Additionally, each question compiles 2 versions: one executable with asserts enabled, and one with asserts disabled (compiled with -DNDEBUG). Executables with `-test` in their name have asserts enabled.

```shell
make         # preform target 'all' by default
make all     # compile all files (with and without asserts)
make dev     # compile all files (with asserts)
make prod    # compile all files (without asserts)
make clean   # remove all compiled files

./a3q1-test  # run question 1 with asserts
./a3q1       # run question 1 without asserts

./a3q2-test  # run question 2 with asserts
./a3q2       # run question 2 without asserts
```

Note: for Question 2 the program reads in text from the STDIN until it reaches a EOF character. Thus to run the application and redirect a text file as the input, use the following:

```shell
./a3q2 < textFile.txt
```
