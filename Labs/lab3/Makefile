all: testing

testing: testing.c binsearch.c
	clang -include binsearch.h -c binsearch.c
	clang -Wall -g binsearch.c testing.c -o testing

prod:
	clang -include binsearch.h -c binsearch.c
	clang -Wall -DNDEBUG -g binsearch.c testing.c -o testing