CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
CC = clang

all: Duplicates Solver

duplicates: duplicates.c
	$(CC) $(CFLAGS) duplicates.c -o duplicates

solver: solver.c
	$(CC) $(CFLAGS) solver.c -o solver

clean:
	rm -f duplicates solver
