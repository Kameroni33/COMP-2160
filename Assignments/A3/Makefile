CC       = clang
CCFLAGS  = -Wall -g
OBJFILES = orderedList.o
PROGRAMS = a3q1 a3q2

all: $(OBJFILES) $(PROGRAMS)

# Compile OBJFILES
orderedList.o: orderedList.c
	$(CC) $(CCFLAGS) -c orderedList.c -o orderedList.o

# Compile PROGRAMS and link OBJFILES
$(PROGRAMS): %: %.c orderedList.o
	$(CC) $(CCFLAGS) $< orderedList.o -o $@

# Remove OBJFILES and PROGRAMS
clean:
	rm -f $(OBJFILES) $(PROGRAMS)
