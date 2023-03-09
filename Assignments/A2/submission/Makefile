CFLAGS = -Wextra -Wpedantic -Werror -g
CC = clang

all: maze

maze: maze.c
	$(CC) -Wall maze.c -o maze

development:
	$(CC) -Wall $(CFLAGS) maze.c -o maze

production:
	$(CC) -Wall -DNDEBUG maze.c -o maze

clean:
	rm -f maze