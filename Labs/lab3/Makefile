all: testing

testing: testing.c binsearch.c
	clang -include binsearch.h -c binsearch.c
	clang -Wall -g -o testing binsearch.c testing.c
