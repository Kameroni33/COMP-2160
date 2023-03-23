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
ifeq($(TYPE),development)
$(PROGRAMS): %: %.c orderedList.o
		$(CC) $(CCFLAGS) -Wextra -Wpedantic -Werror $< orderedList.o -o $@
else
$(PROGRAMS): %: %.c orderedList.o
	$(CC) $(CCFLAGS) -DNDEBUG $< orderedList.o -o $@
endif

# Remove OBJFILES and PROGRAMS
clean:
	rm -f $(OBJFILES) $(PROGRAMS)
