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
    int testLen1 = 4;
    int testLen2 = 5;
    int testLen3 = 10;
    char *testWords1[MAX_WORD] = {"apple", "calculs", "cow", "camp"};
    char *testWords2[MAX_WORD] = {"apple", "calculs", "cow", "camp", "camel"};
    char *testWords3[MAX_WORD] = {"apple", "art", "avocado", "bee", "camp", "egg", "hello", "home", "puzzle", "zoo"};

    testOrderedList(testWords1, testLen1, 3, 3);
    testOrderedList(testWords2, testLen2, 4, 4);
    testOrderedList(testWords3, testLen3, 13, 4);

    printf("\n");
    printf("testsTotal:  %d\n", testsTotal);
    printf("testsPassed: %d\n", testsPassed);
    printf("testsFailed: %d\n", testsFailed);

    printf("\nEnd of Program.\n");
    return 0;
}

void testOrderedList(char *words[], int numWords, int expectedInsertTraversals, int expectedFindTraversals)
{
    boolean passed = true;
    int insertTraversals;
    int findTraversals;

    List *list = construct();

    for (int i = 0; i < numWords; i++)
    {
        boolean result = insert(list, words[i]);
        if (!result)
        {
            printf("insert failed\n");
            passed = false;
        }
        print(list);
        printf("traversals: %d\n", traversals());
    }

    // check number of insert traversals
    insertTraversals = traversals() - lastTraversals;
    lastTraversals = traversals();
    if (insertTraversals != expectedInsertTraversals)
    {
        passed = false;
        printf("insert traversals is %d, expected %d\n", insertTraversals, expectedInsertTraversals);
    }
    

    for (int i = 0; i < numWords; i++)
    {
        boolean result = find(list, words[i]);
        if (!result)
        {
            printf("find failed\n");
            passed = false;
        }
    }

    // check number of find traversals
    findTraversals = traversals() - lastTraversals;
    lastTraversals = traversals();
    if (findTraversals != expectedFindTraversals)
    {
        passed = false;
        printf("find traversals is %d, expected %d\n", findTraversals, expectedFindTraversals);
    }

    if (size(list) != numWords)
    {
        passed = false;
        printf("node count is %d, expected %d\n", size(list), numWords);
    }

    destroy(list);

    // update counters
    if (passed)
    {
        testsPassed++;
    }
    else
    {
        testsFailed++;
    }

    testsTotal++;
    printf("\n");
}
