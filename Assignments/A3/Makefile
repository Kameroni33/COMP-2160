CC = clang
CCFLAGS = -Wall -Wextra -Wpedantic -Werror -g 
OBJFILES = orderedList.o
PROGRAMS = a3q1 a3q2

all: $(OBJFILES) $(PROGRAMS) $(PROGRAMS)-test

prod: $(OBJFILES) $(PROGRAMS)

dev: $(OBJFILES) $(PROGRAMS)-test

# Compile OBJFILES
orderedList.o: orderedList.c
	$(CC) $(CCFLAGS) -c orderedList.c -o orderedList.o

# Compile PROGRAMS and link OBJFILES (without asserts)
$(PROGRAMS): %: %.c orderedList.o
	$(CC) $(CCFLAGS) -DNDEBUG $< orderedList.o -o $@

# Compile PROGRAMS and link OBJFILES (with asserts)
$(PROGRAMS)-test: $(PROGRAMS:-test)

$(PROGRAMS:-test): %-test: %.c orderedList.o
	$(CC) $(CCFLAGS) -DNDEBUG $< orderedList.o -o $@

# Remove OBJFILES and PROGRAMS
clean:
	rm -f $(OBJFILES) $(PROGRAMS) $(PROGRAMS)-test
