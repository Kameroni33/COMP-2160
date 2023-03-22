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
static int lastTraversals;

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

    // Test Cases
    int testLen1 = 10;
    char *testWords1[MAX_WORD] = {"apple", "art", "avocado", "bee", "camp", "egg", "hello", "home", "puzzle", "zoo"};

    testOrderedList(testWords1, testLen1, 90);
    testOrderedList(testWords1, testLen1, 90);

    printf("testsTotal:  %d\n", testsTotal);
    printf("testsPassed: %d\n", testsPassed);
    printf("testsFailed: %d\n", testsFailed);

    printf("\nEnd of Program.\n");
    return 0;
}

void testOrderedList(char *words[], int numWords, int expectedTraversals)
{
    boolean passed = false;
    int currTraversals;
    // create a new list to test
    List *list = construct();

    printf("Testing...\n");

    // printf("\n");
    for (int i = 0; i < numWords; i++)
    {
        boolean result = insert(list, words[i]);
        // printf("insert(\"%s\") = %d\n", words[i], result);
    }

    // printf("\n");
    for (int i = 0; i < numWords; i++)
    {
        boolean result = find(list, words[i]);
        // printf("find(\"%s\") = %d\n", words[i], result);
    }

    // printf("\n");
    // print(list);
    // printf("\n");

    // create a new list to test
    destroy(list);

    // calculate number of traversals for the current test
    currTraversals = traversals() - lastTraversals;
    lastTraversals = traversals();
    // check if we had the number of expected traversals
    if (expectedTraversals == currTraversals)
    {
        passed = true;
    }
    printf("traversals = %d\n\n", currTraversals);

    // update counters
    if (passed) testsPassed++;
    else testsFailed++;
    testsTotal++;
}
