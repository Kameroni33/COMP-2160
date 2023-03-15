CFLAGS = -Wall -g
CC     = clang

all: maze board

maze: maze.c
	$(CC) $(CFLAGS) maze.c -o maze

board: board.c
	$(CC) $(CFLAGS) board.c -o board

clean:
	rm -f board
