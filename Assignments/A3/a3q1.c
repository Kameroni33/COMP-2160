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
void testCase(char *words[], int numWords, int expectedInsertFailures, int expectedFindFailures, int expectedInsertTraversals, int expectedFindTraversals, int expectedFinalLength);

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
    testsTotal = 0;
    testsPassed = 0;
    testsFailed = 0;
    lastTraversals = 0;
    testsNum = 1;

    // Test Cases
    char *testWords1[MAX_WORD] = {"apple", "calculus", "cow", "camp"};
    char *testWords2[MAX_WORD] = {"apple", "calculus", "cow", "camp", "camel"};
    char *testWords3[MAX_WORD] = {"apple", "calculus", "cow", "camp", "cafe"};
    char *testWords4[MAX_WORD] = {"apple", "art", "avocado", "bee", "camp", "egg", "hello", "home", "puzzle", "zoo"};
    char *testWords5[MAX_WORD] = {"zoo", "puzzle", "home", "hello", "egg", "camp", "bee", "avocado", "art", "apple"};
    char *testWords6[MAX_WORD] = {"", "", ""};
    char *testWords7[MAX_WORD] = {"word", "word", "word"};

    printf("==================================================\n");
    printf("Testing Ordered List Library\n");
    printf("==================================================\n");

    // test normal cases
    testCase(testWords1, 4, 0, 0, 3, 3, 4);     // normal list (unsorted)
    testCase(testWords2, 5, 0, 0, 4, 6, 5);     // namarl list (inserted by index)
    testCase(testWords3, 5, 0, 0, 4, 6, 5);     // namarl list (replace index entry)

    // test edge cases
    testCase(testWords4, 10, 0, 0, 13, 4, 10);  // forward alphabetical ordered list
    testCase(testWords5, 10, 0, 0, 0, 4, 10);   // backward alphabetical ordered list

    // test special cases
    testCase(testWords6, 3, 3, 3, 0, 0, 0);     // list of empty entries
    testCase(testWords7, 3, 0, 0, 0, 0, 3);     // list of duplicate entries

    printf("\n==================================================\n");
    printf("testsTotal:  %d\n", testsTotal);
    printf("testsPassed: %d\n", testsPassed);
    printf("testsFailed: %d\n", testsFailed);
}

void testCase(char *words[], int numWords, int expectedInsertFailures, int expectedFindFailures, int expectedInsertTraversals, int expectedFindTraversals, int expectedFinalLength)
{
    int insertTraversals;
    int findTraversals;
    int insertFails = 0;
    int findFails = 0;
    int sorted = true;

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

    // check number of insert traversals
    insertTraversals = traversals() - lastTraversals;
    lastTraversals = traversals();

    // find words in list
    for (int i = 0; i < numWords; i++)
    {
        boolean result = find(list, words[i]);
        if (!result)
        {
            findFails++;
        }
    }

    // check number of find traversals
    findTraversals = traversals() - lastTraversals;
    lastTraversals = traversals();

    // black-box test conditions
    printf("insert failures:   %d (expected: %d)\n", insertFails, expectedInsertFailures);
    printf("find failures:     %d (expected: %d)\n", findFails, expectedFindFailures);
    printf("list size:         %d (expected: %d)\n", size(list), expectedFinalLength);
    // white-box test conditions
    printf("insert traversals: %d (expected: %d)\n", insertTraversals, expectedInsertTraversals);
    printf("find traversals:   %d (expected: %d)\n", findTraversals, expectedFindTraversals);

    // destroy list
    destroy(list);

    // check test conditions
    if (insertFails == expectedInsertFailures
        && findFails == expectedFindFailures
        && size(list) == expectedFinalLength
        && insertTraversals == expectedInsertTraversals
        && findTraversals == expectedFindTraversals
        && sorted)
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


