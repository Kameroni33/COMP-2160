CFLAGS = -Wall -g
CC     = clang

all: maze board binsearch

maze: maze.c
	$(CC) $(CFLAGS) maze.c -o maze

board: board.c
	$(CC) $(CFLAGS) board.c -o board

binsearch: binsearch.c
	$(CC) $(CFLAGS) -DNDEBUG binsearch.c -o binsearch

clean:
	rm -f board
