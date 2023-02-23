# COMP 2160: Notes

---

## Safe Input - File I/O (feb. 03, 2023)

### Last class

* secure.c
* scanf() -> bad
* fgets() -> better

### I/O

- `fgets()` lets us pass a _file_

But what even is a file?
- basically a _struct_ that contains information about the file

Opening Files:

1. `fopen()` takes a _file path_ and _open type_ and returns a _file pointer_

```c
FILE *f = fopen("filename.txt", "r");
```

2. Check to see if the file actually opened

```c
if (f == NULL)
{
    printf("File could not be opened.");
    exit(1);
}
```

3. Read the file contents

```c
#define LINE_WIDTH 80
char line[LINE_LENGTH];

FILE *f = fopen("filename.txt", "r");
if (f != NULL)
{
    fgets(line, LINE_WIDTH, f)
}
```

There is also the functions `fscanf`, `fread`, ...

__Remember:__ C does not have exceptions, we need to handle all possible cases

4. Check to see if the function returns NULL (or use a loop)

```c
if (f != NULL)
{
    while (fgets(line, LINE_WIDTH, f) != NULL)
    {
        printf("%s\n", line);
    }
}
```

5. Close the file

```c
// ... process file
fclose(f);
```

### Resource Managements

- Java & Python are garbage collected
- C is no garbage collected
    - as a veriable goes out of scope, the resource is not reclaimed (memory leak)


### Structs

A _struct_ is a named group of related data.

```c
struct SCIENTIFIC_NOTATION
{
    unsigned int base;
    unsigned int exponent;
};
```

### Privacy

In c we don't have a concept of information hiding. Everything is effectively _public_.



---

## More File I/O (feb. 06, 2023)

### Writing Files

1. Open file (we've already seen how to do this last lecture)

2. Write to file

We've been writing to a file this whole time (`printf` writes to "standard output" by default)

- `stdout` is a file
    - `printf` writes to `FILE *stdout`
    - `fprintf` lets us specify a file pointer

3. Close file

But only if you could actually open the file in the first place

### Resource Management

Keep in mind that C is not garbage collected. Thus we must be careful to close our files.

- _`scanf` does not check the size of the memory we write into (typically unsafe to use)_
- _`fgets` lets us specify how much memory we can write to (usually safer)_
- _Everything is a file (... on a UNIX system)_

### Classes

What is a class?

- A generic representation of a common object
- Methods to create and modify specific instances of that object

we don't have classes in C, but we do have...

### Structs

- do not methods nor any concept of privacy.
- contain a fixed number of parts (can be different types)

```c
struct friendStruct {       // every struct needs a name
    char name[MAXNAME];     // parts of a struct are known as 'members' 
    long phoneNumber;
    char street[MAXSTREET];
};                          // this declares a `type` of struct, not an instance
```

Then to declare a struct

```c
struct friendStruct kam;

kam.name = "Kameron";       // . operator gives us access to the value of kam's name
kam.phoneNumber;
...
```

We can give our structs  an aliase by using the `typedef` keyword.

```c
typedef struct friendStruct friend;

friend kam;
```

Or a shortcut is to define the aliase directly after the struct definition.

```c
struct friendStruct {
    ...
}friend;
```

__NOTE:__ _we can actually return a type of struct because it has a fixed size in memory (allocated). Whereas with an array, we don't necessarily know its size and thus cannot return it._



---

## File I/O - Struct (feb. 08, 2023)

### Structures

- for a limited number of elements
- of varying types
- which need to be kept together, in one place

In C, a structure is known as `struct`

### Declaring & Accessing Structs

_refer to last class_.

### Operations on Structures

- Assignment of structures

```c
struct StudentRed studA, studB;
strudA = studB;
```

This copies studB.id into studA.id, studB.mark into studA.mark, etc... (_because structures are well defined as far as memory allocation_)

Note: _we can use this to conveniently copy arrays inside structs_

- structs cannot be compared
- we can compare member comparison only

### Accessing Members with Pointers

- Using the dot operator `.` and dereference operator `*`. Note that the dot operator has higher priority, so we need parenthesis when accessing a struct using a pointer

```c
(*fptr).numerator++;
```

- Using the `->` operator

```c
fptr->numerator++;
```

### Passing a struct to a function

- As always, the formal parameters are copies of the actual parameters (new allocated memory space).
- we can return a struct directly


---

## Design by Contract (feb. 15, 2023)

### Review

When allocating data with `malloc`:
- you can allocate memory *without* actually passing it to a pointer (but then we don't know where it is allocated).
- you can allocate it to *any* type of pointer (technically)

### Design by Contract

An approach for designing software:

- conditions and invariants

A tool to prevent progrming errors (*not* language specific)

- this is code you write that encodes your assumptions about inputs, outputs, and state of your program.

Exceptions come from a violation of our assumptions (usually). There are 3 places our assumptions can be violated:

1. before we startprocessing
2. after we finish processing 
3. the state of an object throughout execution

### Conditions

Preconditions:

- check the inputs to a function/block/concept meet certain conditions

Postconditions:

- check the outputs of a function/block/concept meet certain conditions

#### Ex. Preconditions

```c
void init_list(char *word) {}
```

Assumptions:
- head == NULL  (have not initialized the list before)
- word != NULL  (need actual data to create a list from)

### Invariants

- we're focusing on class and type invariants
- verify that an object or data meets certain conditions during execution (state)
- usually implemented as a function
    - often called in pre- and post-condition (invariants complement conditions)

#### Ex. Invariants

- number of nodes actually in the list reflects the integer variable counting the number of nodes.
- if the list is empty, head == NULL and count == 0

### Implementing

- encode using `assert`s
- asserts test for 'truthfullness'

```c
#include <assert.h>

int value = 10;
assert( value > 0);
```
