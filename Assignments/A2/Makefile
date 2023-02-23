CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
CC = clang

all: maze

maze: maze_start.c
	$(CC) $(CFLAGS) maze_start.c -o maze

clean:
	rm -f maze