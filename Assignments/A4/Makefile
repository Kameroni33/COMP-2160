CC = clang
FLAGS = -Wall -g -Wextra -Wpedantic -Werror

all: ObjectManager main main-test

dev: ObjectManager main-test

prod: ObjectManager main

# Compile object files
ObjectManager: ObjectManager.c
	$(CC) $(FLAGS) -DNDEBUG -c ObjectManager.c -o ObjectManager.o
	$(CC) $(FLAGS) -c ObjectManager.c -o ObjectManager-test.o

# Compile with ASSERTS
main: main.c ObjectManager.o
	$(CC) $(FLAGS) -DNDEBUG main.c ObjectManager.o -o main

# Compile without ASSERTS
main-test: main.c ObjectManager.o
	$(CC) $(FLAGS) main.c ObjectManager-test.o -o main-test

# Remove OBJFILES and PROGRAMS
clean:
	rm -f ObjectManager.o ObjectManager-test.o main main-test
