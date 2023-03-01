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
    int array2[] = { 1, 3, 4, 7, 9, 14, 26, 31 };
    int array3[] = { 0, 0, 0 };
    int array4[] = { 1 };
    int array5[] = { -3, -2, -1, 0 };

    printf("Testing typical cases\n");

    test_binary_search(0, 1, array1, 3);
    test_binary_search(1, 2, array1, 3);
    test_binary_search(2, 3, array1, 3);
    test_binary_search(-1, 4, array1, 3);

    test_binary_search(3, 7, array2, 8);
    test_binary_search(6, 26, array2, 8);
    test_binary_search(-1, 24, array2, 8);

    test_binary_search(1, 0, array3, 3);

    test_binary_search(0, 1, array4, 1);

    test_binary_search(0, -3, array5, 4);
    test_binary_search(2, -1, array5, 4);
    test_binary_search(3, 0, array5, 4);
    test_binary_search(-1, -4, array5, 4);

}