# COMP 2160 - Assignment 3

Kameron Ronald  
ronaldk1@myumanitoba.ca  
7880495  

## Compiling & Running

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

For Question 2 the program reads in text until it reaches a EOF character. It's usage is:

```shell
./a3q2 < textFile.txt
```
