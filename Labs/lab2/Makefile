FLAGS = -Wall

all: test_clean test_last

test_clean: test_clean.c
	clang $(FLAGS) test_clean.c -o test_clean

test_last: test_last.c
	clang $(FLAGS) test_last.c -o test_last

run:
	./test_clean
	./test_last

clean:
	rm test_clean test_last