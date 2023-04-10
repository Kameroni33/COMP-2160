#include "ObjectManager.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("argc: %d\nargv[0]: %s\n\n", argc, argv[0]);

    char *ptr;
    int i;
    int id1, id2, id3;

    printf("Initialing Pool...\n");
    initPool();  // initialize ObjectManager

    printf("Allocating 100 to id1...\n");
    id1 = insertObject(100);
    ptr = (char*)retrieveObject(id1);
    for (i = 0; i < 100; i++)
        ptr[i] = (char)(i%26 + 'A');
    
    printf("Allocating 4000 to id2...\n");
    id2 = insertObject(4000);

    printf("Allocating 20200 to id3...\n");
    id3 = insertObject(20200);

    dumpPool();

    // drop reference to id3
    printf("droping reference id3...\n");
    dropReference(id3);

    dumpPool();

    // allocate 10 to id3
    printf("Allocating 10 to id3...\n");
    id3 = insertObject(10);

    dumpPool();
    
    // print contents of id1 to stderr
    printf("Printing contents of id1...\n");
    ptr = (char*)retrieveObject(id1);
    for (i = 0; i < 100; i++)
        fprintf(stderr,"%c",ptr[i]);
    fprintf(stderr,"\n");
    
    dumpPool();

    destroyPool();

    fprintf(stderr,"---\n");

    dropReference(id2);  // cuz its not used... (compiler warnings)

    printf("End of Process.\n");
    return 0;
}

