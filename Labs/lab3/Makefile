
all: binsearch testing

binsearch: binsearch.c
	clang -Wall -g -o binsearch binsearch.c

testing: testing.c binsearch.c
	clang -Wall -g -o testing binsearch.c testing.c
