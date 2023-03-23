CC = clang
CCFLAGS = -Wall -g
OBJFILES = orderedList.o
TEST_PROGRAMS = a3q1-test a3q2-test
PROD_PROGRAMS = a3q1 a3q2

all: $(OBJFILES) $(TEST_PROGRAMS) $(PROD_PROGRAMS)

dev: $(OBJFILES) $(TEST_PROGRAMS)

prod: $(OBJFILES) $(PROD_PROGRAMS)

# Compile OBJFILES
orderedList.o: orderedList.c
	$(CC) $(CCFLAGS) -c orderedList.c -o orderedList.o

# Compile PROGRAMS and link OBJFILES (with asserts)
$(TEST_PROGRAMS): %: %.c orderedList.o
	$(CC) $(CCFLAGS) -Wextra -Wpedantic -Werror $< orderedList.o -o $@

# Compile PROGRAMS and link OBJFILES (without asserts)
$(PROD_PROGRAMS): %: %.c orderedList.o
	$(CC) $(CCFLAGS) -DNDEBUG $< orderedList.o -o $@

# Remove OBJFILES and PROGRAMS
clean:
	rm -f $(OBJFILES) $(TEST_PROGRAMS) $(PROD_PROGRAMS)
