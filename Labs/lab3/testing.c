#include <stdio.h>
// include binsearch.c file for testing
#include "binsearch.h"

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
static int tests_executed = 0;
static int tests_failed = 0;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------
void test_binary_search(int expected, int key, int array[], int count);
void test_typical_cases();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------
int main()
{
  printf("Beginning tests\n\n");
  test_typical_cases();
  
  // test more stuff...

  printf("\nTotal number of tests executed: %d\n", tests_executed);
  printf("Number of tests passed:         %d\n", (tests_executed - tests_failed));
  printf("Number of tests failed:         %d\n", tests_failed);
  
  return 0;
}

void test_binary_search(int expected, int key, int array[], int count)
{
    int result = binsearch(key, array, count);

    if (result == expected)
    {
        printf("Passed: %d searching for '%d' in array length %d\n", result, key, count);
    }
    
    else
    {
        printf("FAILED: %d instead of %d searching for '%d' in array length %d\n", result, expected, key, count);
        tests_failed++;
    }

    tests_executed++;
}

void test_typical_cases()
{
    int array1[] = { 1, 2, 3 };

    printf("Testing typical cases\n");

    test_binary_search(1, 2, array1, 3);

    // test more stuff...
}

void test_edge_cases()
{
    int array1[] = { 1, 2, 3 };

    printf("Testing edge cases\n");

    test_binary_search(1, 2, array1, 3);

    // test more stuff...
}