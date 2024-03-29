#include <assert.h>
#include <stddef.h>

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
