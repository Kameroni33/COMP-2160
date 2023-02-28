#include <assert.h>
#include <stddef.h>

int binsearch(int target, int array[], int arrayLen)
{
    //---------------------------------------------------------------------------------
    // Pre-Conditions
    //---------------------------------------------------------------------------------
    assert(array != NULL);

    // assert(arrayLen == sizeof(array)/sizeof(array[0]));

    //---------------------------------------------------------------------------------
    // Algorithm
    //---------------------------------------------------------------------------------
    int left, right, center;

    left = 0;
    right = arrayLen - 1;
    while (left <= right)
    {
        center = (left + right) / 2;

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


            return center;
        }
    }

    //---------------------------------------------------------------------------------
    // Post-Conditions (case 2)
    //---------------------------------------------------------------------------------


    return -1;
}
