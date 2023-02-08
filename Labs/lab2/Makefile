FLAGS = -Wall

all: test_clean test_last

test_clean: test_clean.c
	clang $(FLAGS) test_clean.c -o test_clean

test_last: test_last.c
	clang $(FLAGS) sitest_lastgn.c -o test_last

clean:
	rm excercise test_clean test_last