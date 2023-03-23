CC = clang
CCFLAGS = -Wall -Wextra -Wpedantic -Werror -g 
OBJFILES = orderedList.o
PROGRAMS = a3q1 a3q2
TEST_PROGRAMS = a3q1-test a3q2-test

all: $(OBJFILES) $(PROGRAMS) $(TEST_PROGRAMS)

prod: $(OBJFILES) $(PROGRAMS)

dev: $(OBJFILES) $(TEST_PROGRAMS)

# Compile OBJFILES
orderedList.o: orderedList.c
	$(CC) $(CCFLAGS) -c orderedList.c -o orderedList.o

# Compile PROGRAMS and link OBJFILES (without asserts)
$(PROGRAMS): %: %.c orderedList.o
	$(CC) $(CCFLAGS) -DNDEBUG $< orderedList.o -o $@

# Compile PROGRAMS and link OBJFILES (with asserts)
$(TEST_PROGRAMS): %-test: %.c orderedList.o
	$(CC) $(CCFLAGS) -DNDEBUG $< orderedList.o -o $@

# Remove OBJFILES and PROGRAMS
clean:
	rm -f $(OBJFILES) $(PROGRAMS) $(TEST_PROGRAMS)
