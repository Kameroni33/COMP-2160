#include "ObjectManager.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("argc: %d\nargv[0]: %s\n\n", argc, argv[0]);

    char *ptr;
    int i;
    int id1, id2, id3, id4, id5, id6, id7, id8, id9, id10, id11, id12;
    int result;

    printf("==================================================\n");
    printf("OBJECT MANAGER TEST (Memory Size: %d)\n", MEMORY_SIZE);
    printf("==================================================\n");

    printf("1) Initialing Pool...\n");
    initPool();

    dumpPool();

    // 524288

    printf("2) Allocating memory the following...\n\n");
    printf(" ID 1: 2342 bytes (A)\n");
    printf(" ID 2: 645 bytes (B)\n");
    printf(" ID 3: 67890 bytes (C)\n");
    printf(" ID 4: 153 bytes (D)\n");
    printf(" ID 5: 215438 bytes (E)\n");
    printf(" ID 6: 42 bytes (F)\n");
    printf(" ID 7: 132456 bytes (G)\n");
    printf(" ID 8: 4536 bytes (H)\n");
    printf(" ID 9: 73567 bytes (I)\n");

    id1 = insertObject(2342);
    id2 = insertObject(645);
    id3 = insertObject(67890);
    id4 = insertObject(153);
    id5 = insertObject(215438);
    id6 = insertObject(42);
    id7 = insertObject(132456);
    id8 = insertObject(4536);
    id9 = insertObject(73567);

    ptr = (char*)retrieveObject(id1);
    for (i = 0; i < 2342; i++)
        ptr[i] = 'A';
    ptr = (char*)retrieveObject(id2);
    for (i = 0; i < 645; i++)
        ptr[i] = 'B';
    ptr = (char*)retrieveObject(id3);
    for (i = 0; i < 67890; i++)
        ptr[i] = 'C';
    ptr = (char*)retrieveObject(id4);
    for (i = 0; i < 153; i++)
        ptr[i] = 'D';
    ptr = (char*)retrieveObject(id5);
    for (i = 0; i < 215438; i++)
        ptr[i] = 'E';
    ptr = (char*)retrieveObject(id6);
    for (i = 0; i < 42; i++)
        ptr[i] = 'F';
    ptr = (char*)retrieveObject(id7);
    for (i = 0; i < 132456; i++)
        ptr[i] = 'G';
    ptr = (char*)retrieveObject(id8);
    for (i = 0; i < 4536; i++)
        ptr[i] = 'H';
    ptr = (char*)retrieveObject(id9);
    for (i = 0; i < 73567; i++)
        ptr[i] = 'I';

    printf("Expected Total Memory Usage: %d\n", 2342 + 645 + 67890 + 153 + 215438 + 42 + 132456 + 4536 + 73567);
    
    dumpPool();

    // drop reference to id3
    printf("3) Dropping references to ID's 1, 4, 6, and 9...\n");
    dropReference(id1);
    dropReference(id4);
    dropReference(id6);
    dropReference(id9);

    printf("Expected Total Memory Usage: %d\n", 645 + 67890 + 215438 + 132456 + 4536);

    dumpPool();

    // allocate 10 to id3
    printf("4) Allocating memory the following...\n\n");
    printf(" ID 10: 1946 bytes (J)\n");
    printf(" ID 11: 103923 bytes (K)\n");
    printf(" ID 12: 853 bytes (L)\n\n");

    id10 = insertObject(1946);
    id11 = insertObject(213849);
    id12 = insertObject(853);

    ptr = (char*)retrieveObject(id10);
    for (i = 0; i < 1946; i++)
        ptr[i] = 'J';
    ptr = (char*)retrieveObject(id11);
    for (i = 0; i < 213849; i++)
        ptr[i] = 'K';
    ptr = (char*)retrieveObject(id12);
    for (i = 0; i < 853; i++)
        ptr[i] = 'L';

    printf("Expected call to COMPACT\n");
    printf("Expected Total Memory Usage: %d\n", 645 + 67890 + 215438 + 132456 + 4536 + 1946 + 213849 + 853);

    dumpPool();

    printf("5) Check contents of memory for the following...\n\n");

    result = 1;
    ptr = (char*)retrieveObject(id2);
    for (i = 0; i < 645; i++)
        if (ptr[i] != 'B') result = 0;
    printf(" ID 2: %s\n", result ? "success" : "failure");

    result = 1;
    ptr = (char*)retrieveObject(id3);
    for (i = 0; i < 67890; i++)
        if (ptr[i] != 'C') result = 0;
    printf(" ID 3: %s\n", result ? "success" : "failure");

    result = 1;
    ptr = (char*)retrieveObject(id5);
    for (i = 0; i < 215438; i++)
        if (ptr[i] != 'E') result = 0;
    printf(" ID 5: %s\n", result ? "success" : "failure");

    result = 1;
    ptr = (char*)retrieveObject(id7);
    for (i = 0; i < 132456; i++)
        if (ptr[i] != 'G') result = 0;
    printf(" ID 7: %s\n", result ? "success" : "failure");

    result = 1;
    ptr = (char*)retrieveObject(id8);
    for (i = 0; i < 4536; i++)
        if (ptr[i] != 'H') result = 0;
    printf(" ID 8: %s\n", result ? "success" : "failure");

    result = 1;
    ptr = (char*)retrieveObject(id10);
    for (i = 0; i < 1946; i++)
        if (ptr[i] != 'J') result = 0;
    printf(" ID 10: %s\n", result ? "success" : "failure");

    result = 1;
    ptr = (char*)retrieveObject(id11);
    for (i = 0; i < 213849; i++)
        if (ptr[i] != 'K') result = 0;
    printf(" ID 11: %s\n", result ? "success" : "failure");

    result = 1;
    ptr = (char*)retrieveObject(id12);
    for (i = 0; i < 853; i++)
        if (ptr[i] != 'L') result = 0;
    printf(" ID 12: %s\n", result ? "success" : "failure");

    destroyPool();

    printf("End of Process.\n");
    return 0;
}

