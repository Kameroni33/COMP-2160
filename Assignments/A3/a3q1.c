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
            print("<insert failed>\n");
            passed = false;
        }
    }

    // check number of insert traversals
    insertTraversals = traversals() - lastTraversals;
    lastTraversals = traversals();
    if (insertTraversals != expectedInsertTraversals)
    {
        passed = false;
    }
    printf("insert() traversals = %d\n", insertTraversals);

    for (int i = 0; i < numWords; i++)
    {
        boolean result = find(list, words[i]);
        if (!result)
        {
            print("<find failed>\n");
            passed = false;
        }
    }

    // check number of find traversals
    findTraversals = traversals() - lastTraversals;
    lastTraversals = traversals();
    if (findTraversals != expectedFindTraversals)
    {
        passed = false;
    }
    printf("find() traversals = %d\n", findTraversals);

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
}
