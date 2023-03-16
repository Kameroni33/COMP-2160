#include <stdio.h>
#include <assert.h>
#include <stddef.h>

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
static int tests_executed = 0;
static int tests_failed = 0;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------
int binsearch(int target, int array[], int arrayLen);
void test_binary_search(int expected, int key, int array[], int count);
void test_typical_cases();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

int binsearch(int target, int array[], int arrayLen)
{
    //---------------------------------------------------------------------------------
    // Pre-Conditions
    //---------------------------------------------------------------------------------
    assert(array != NULL);
    assert(arrayLen >= 0);
    assert(target >= array[0]);
    assert(target <= array[arrayLen-1]);

    for (int i = 0; i < arrayLen-1; i++)
    {
        assert(array[i] <= array[i+1]);
    }

    //---------------------------------------------------------------------------------
    // Algorithm
    //---------------------------------------------------------------------------------
    int left, right, center;

    left = 0;
    right = arrayLen - 1;
    while (left <= right)
    {
        center = (left + right) / 2;

        // assert that center is a valid number at this point
        assert(center >= 0);
        assert(center >= left);
        assert(center <= right);

        if(target < array[center])
        {
            right = center-1;
        }

        else if (target > array[center])
        {
            left = center+1;
        }

        else
        {
            //-------------------------------------------------------------------------
            // Post-Conditions (case 1)
            //-------------------------------------------------------------------------
            assert(array[center] == target);
            assert(array[center] >= array[0]);
            assert(array[center] <= array[arrayLen-1]);

            return center;
        }
    }

    //---------------------------------------------------------------------------------
    // Post-Conditions (case 2)
    //---------------------------------------------------------------------------------
    assert(left > right);

    return -1;
}

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
    int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    //invalid test
    test_binary_search(4, 4, array, -1);

}