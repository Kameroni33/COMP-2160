#include <stdio.h>
#include <assert.h>
#include "orderedList.h"

#define MAX_WORD 100

//=====================================================================================
// Global Variables
//=====================================================================================
static int testsTotal;
static int testsPassed;
static int testsFailed;
static int lastTraversals;
static int testsNum;

//=====================================================================================
// Function Prototypes
//=====================================================================================
void testOrderedList();
void testNormalCase(char *words[], int numWords, int expectedInsertTraversals, int expectedFindTraversals);

//=====================================================================================
// Function Definitions
//=====================================================================================
int main( int argc, char *argv[] )
{
    printf("program: %s\nargc: %d\n\n", argv[0]+2, argc);

    testOrderedList();

    printf("\nEnd of Program.\n");
    return 0;
}

void testOrderedList()
{
    // Test Cases
    char *testWords1[MAX_WORD] = {"apple", "calculus", "cow", "camp"};
    char *testWords2[MAX_WORD] = {"apple", "calculus", "cow", "camp", "camel"};
    char *testWords3[MAX_WORD] = {"apple", "art", "avocado", "bee", "camp", "egg", "hello", "home", "puzzle", "zoo"};
    char *testWords4[MAX_WORD] = {"", "", ""};

    printf("==================================================\n");
    printf("Testing Ordered List Library\n");
    printf("==================================================\n");

    // WHITE BOX TESTS ================================================================

    // test normal cases
    testNormalCase(testWords1, 4, 3, 3);
    testNormalCase(testWords2, 5, 4, 6);
    testNormalCase(testWords3, 10, 13, 4);

    // test edge cases

    // test special cases
    testNormalCase(testWords4, 3, 0, 0);

    // BLACK BOX TESTS ================================================================

    printf("\n==================================================\n");
    printf("testsTotal:  %d\n", testsTotal);
    printf("testsPassed: %d\n", testsPassed);
    printf("testsFailed: %d\n", testsFailed);
}

void testNormalCase(char *words[], int numWords, int expectedInsertTraversals, int expectedFindTraversals, int expectedLength)
{
    int insertTraversals;
    int findTraversals;
    int insertFails = 0;
    int findFails = 0;

    // print test header
    printf("\n==================================================\n");
    printf("Test %d: {", testsNum);
    for (int i = 0; i < numWords; i++)
    {
        printf("\"%s\"", words[i]);
        if (i < numWords - 1) printf(", ");
    }
    printf("}\n");
    testsNum++;

    // create list
    List *list = construct();

    // insert words into list
    for (int i = 0; i < numWords; i++)
    {
        boolean result = insert(list, words[i]);
        if (!result)
        {
            insertFails++;
        }
    }
    printf("%d insert failures\n", insertFails);

    // check number of insert traversals
    insertTraversals = traversals() - lastTraversals;
    lastTraversals = traversals();
    printf("%d insert traversals, expected %d\n", insertTraversals, expectedInsertTraversals);

    // find words in list
    for (int i = 0; i < numWords; i++)
    {
        boolean result = find(list, words[i]);
        if (!result)
        {
            findFails++;
        }
    }
    printf("%d find failures\n", findFails);

    // check number of find traversals
    findTraversals = traversals() - lastTraversals;
    lastTraversals = traversals();
    printf("%d find traversals, expected %d\n", findTraversals, expectedFindTraversals);

    // destroy list
    destroy(list);

    // check if test passed
    if (insertFails == 0 && findFails == 0 && size(list) == expectedLength && insertTraversals == expectedInsertTraversals && findTraversals == expectedFindTraversals)
    {
        testsPassed++;
        printf("Test Passed.\n");
    }
    else
    {
        testsFailed++;
        printf("Test Failed.\n");
    }
    testsTotal++;
}


