CC       = clang
CCFLAGS  = -Wall -g
OBJFILES = orderedList.o
PROGRAMS = a3q1 a3q2

all: $(OBJFILES) $(PROGRAMS)

# Compile Object File(s)
orderedList.o: orderedList.c
	$(CC) $(CCFLAGS) -c orderedList.c -o orderedList.o

# Compile Programs and link Object Files
$(PROGRAMS): %: %.c orderedList.o
	$(CC) $(CCFLAGS) $< orderedList.o -o $@

clean:
	rm -f $(OBJFILES) $(PROGRAMS)
