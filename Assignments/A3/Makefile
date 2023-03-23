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
$(PROGRAMS): %: %.c orderedList.o
	$(CC) $(CCFLAGS) $< orderedList.o -o $@

# Compile PROGRAMS and link OBJFILES (without asserts)
$(PROGRAMS): %: %.c orderedList.o
	$(CC) $(CCFLAGS) $< orderedList.o -o $@

# Remove OBJFILES and PROGRAMS
clean:
	rm -f $(OBJFILES) $(PROGRAMS)
