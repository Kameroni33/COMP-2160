#include <stdio.h>
#include <string.h>
#define SANE_LENGTH 500

struct STRING
{
    char contents[SANE_LENGTH];
    int length;
};

struct STRING make_string(char *);
char char_at(struct STRING , int);
void split (struct STRING, char *, struct STRING[]);

int main(void)
{
#define TOKENS 2
    struct STRING my_string;
    struct STRING my_string_split[TOKENS];

    my_string = make_string("COMP2160isFun");
    printf("Orig = %s \n", my_string.contents);
    split(my_string,"i", my_string_split);

//    printf("%s %d\n", my_string.contents, my_string.length);
    for(int i = 0; i < TOKENS; i++)
    {
        printf("Token %d is %s\n", i, my_string_split[i].contents);
    }

    printf("Orig = %s \n", my_string.contents);

    return 0;
}

void split (struct STRING string, char * delim, struct STRING split_string[])
{
    int index = 0;
    char *next;

    next = strtok(string.contents, delim);
    while(next != NULL)
    {
        struct STRING next_string = make_string(next);
	split_string[index] = next_string;
	index++;
	next = strtok(NULL, delim);        
    }

}

// NOTE: in class this was different:
// * I accepted a pointer to struct STRING, now
//   we just accept struct STRING.
// * We had the -> operator, now we just use .
char char_at(struct STRING string, int loc)
{
    // This is worth 0 if you were to answer
    // a test question about strings with something
    // like this...
    return string.contents[loc];
}

struct STRING make_string(char *string)
{
    struct STRING my_string;
    int i = 0;

    while (string[i] != '\0')
    {
        // copy contents to my_string
        my_string.contents[i] = string[i];
        i++;
    }
    my_string.contents[i] = '\0';

    my_string.length = i;

    return my_string;
}
