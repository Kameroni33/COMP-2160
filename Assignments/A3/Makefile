CC = clang
CCFLAGS = -Wall -g
OBJFILES = orderedList.o
PROGRAMS = a3q1 a3q2

TYPE = development

all: $(OBJFILES) $(PROGRAMS)

dev: $(OBJFILES) $(PROGRAMS)

prod: $(OBJFILES) $(PROGRAMS)

# Compile OBJFILES
orderedList.o: orderedList.c
	$(CC) $(CCFLAGS) -c orderedList.c -o orderedList.o

# Compile PROGRAMS and link OBJFILES (with asserts)
$(PROGRAMS): %: %.c orderedList.o
	ifeq($(TYPE),development)
		$(CC) $(CCFLAGS) -Wextra -Wpedantic -Werror $< orderedList.o -o $@
	else
		$(CC) $(CCFLAGS) -DNDEBUG $< orderedList.o -o $@
	endif

# Remove OBJFILES and PROGRAMS
clean:
	rm -f $(OBJFILES) $(TEST_PROGRAMS) $(PROD_PROGRAMS)
