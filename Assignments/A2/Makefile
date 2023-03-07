CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
CC = clang

all: maze

maze: maze_start.c
	$(CC) -Wall maze_start.c -o maze

development:
	$(CC) $(CFLAGS) maze_start.c -o maze

production:
	$(CC) -Wall -DNDEBUG maze_start.c -o maze

clean:
	rm -f maze