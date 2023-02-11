//-------------------------------------------------------------------------------------------------
// NAME: Kameron Ronald
// STUDENT NUMBER: 7880495
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Saulo dos Santos
// ASSIGNMENT: assignment 1, QUESTION: question 2
// 
// REMARKS: This program is a c implementation of Solver.java.
//-------------------------------------------------------------------------------------------------
#include <stdio.h>

#define MAX_COUNT 30


//-------------------------------------------------------------------------------------------------
// reverse_sort
//
// PURPOSE: sort the given in order from largest -> smallest.
//-------------------------------------------------------------------------------------------------
void reverse_sort(int array[], int array_len) {
    // because we don't have any functions to get the length of an array, we need to pass it in (array_len).
    int max, max_pos;
    for (int i = 0; i < array_len - 1; i++) {
        max = array[i];
        max_pos = -1;
        for (int j = i+1; j < array_len; j++) {
            if (array[j] > max) {
                max = array[j];
                max_pos = j;
            }
        }
        if (max_pos > 0) {
            array[max_pos] = array[i];
            array[i] = max;
        }
    }
}

//-------------------------------------------------------------------------------------------------
// rsolve
//
// PURPOSE: recursively see if the first 'x' values in array add up to the target and return the
//          number of array elements that satisfy this condition (ie. 'x').
//-------------------------------------------------------------------------------------------------
int rsolve (int array[], int unprocessed, int solution[], int solution_count, int so_far, int target) {
    int last_pos, result;

    if (so_far == target) {
        result = solution_count;
    } else if (unprocessed == 0) {
        result = 0;
    } else {
        last_pos = unprocessed - 1;
        result = rsolve(array, last_pos, solution, solution_count, so_far, target);
        if (result == 0 && so_far + array[last_pos] <= target) {
            solution[solution_count] = array[last_pos];
            result = rsolve(array, unprocessed-1, solution, solution_count+1, so_far+array[last_pos], target);
        }
    }

    return result;
}

//-------------------------------------------------------------------------------------------------
// solve
//
// PURPOSE: start the recursive call to rsolve.
//-------------------------------------------------------------------------------------------------
int solve(int array[], int solution[], int target, int array_len) {
    // because we don't have any functions to get the length of an array, we need to pass it in (array_len).
    return rsolve(array, array_len, solution, 0, 0, target);
}

//-------------------------------------------------------------------------------------------------
// main
//-------------------------------------------------------------------------------------------------
int main() {

    int count  = 0;
    int target = 0;
    int solution_count;


    while(1) {
        // read next int from stdin
        scanf("%d", &count);
        if (count > MAX_COUNT) {
            printf("Invalid count: %d.\n", count);
        } else {
            int array[count];  // need to declare here once we have the size
            for (int i = 0; i < count; i++) {
                scanf("%d", &array[i]);
            }
            scanf("%d", &target);

            int solution[count];  // need to declare here once we have the size
            reverse_sort(array, count);
            solution_count = solve(array, solution, target, count);

            if (solution_count > 0) {
                for (int i = 0; i < solution_count; i++) {
                    printf("%d ", solution[i]);
                }
                printf("\n");
            } else {
                printf("Count = %d: no solution.\n", count);
            }
        }
        // get rid of the newline at the end (???)
    }
    
    printf("End of Processing.\n");
    return 0;
}
