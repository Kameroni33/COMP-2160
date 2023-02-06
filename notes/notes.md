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

## More File I/) (feb. 06, 2023)

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




