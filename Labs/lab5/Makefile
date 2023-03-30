CC = clang
CFLAGS = -Wall -g -pg

all: fib fib-cache

fib: fib.c
	$(CC) $(CFLAGS) fib.c -o fib

fib-cache: fib-cache.c
	$(CC) $(CFLAGS) fib-cache.c -o fib-cache

clean:
	rm -f fib fib-cache
