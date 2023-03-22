#include <stdio.h>
#include <assert.h>
#include "orderedList.h"

#define MAX_WORD 20

//=====================================================================================
// Global Variables
//=====================================================================================
static int testsTotal;
static int testsPassed;
static int testsFailed;

//=====================================================================================
// Function Prototypes
//=====================================================================================
static void testOrderedList();

//=====================================================================================
// Function Definitions
//=====================================================================================
int main( int argc, char *argv[] )
{
    printf("program: %s\nargc: %d\n\n", argv[0]+2, argc);

    testOrderedList();

    printf("testsTotal:  %d\n", testsTotal);
    printf("testsPassed: %d\n", testsPassed);
    printf("testsFailed: %d\n", testsFailed);

    int numWords = 10;
    char words[][MAX_WORD] = {"apple", "art", "avocado", "bee", "camp", "egg", "hello", "home", "puzzle", "zoo"};

    List *list = construct();  

    for (int i = 0; i < numWords; i++)
    {
        boolean result = insert(list, words[i]);
        printf("insert(\"%s\") = %d\n", words[i], result);
    }

    printf("\n");

    for (int i = 0; i < numWords; i++)
    {
        boolean result = find(list, words[i]);
        printf("find(\"%s\") = %d\n", words[i], result);
    }

    printf("\n");

    print(list);

    printf("\n");

    printf("\nEnd of Program.\n");
    return 0;
}

void testOrderedList()
{
    testsTotal++;
}
