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
void reverse_sort() {

}

//-------------------------------------------------------------------------------------------------
int solve() {
    return 1;
}

//-------------------------------------------------------------------------------------------------
int resolve () {
    return 1;
}

//-------------------------------------------------------------------------------------------------
// main
//-------------------------------------------------------------------------------------------------
int main() {

    int read_stdin = 1;  // bool to determine if we should read from the stdin input stream

    int count  = 0;
    int target = 0;
    // int* array, solution;
    int solution_count;


    while(read_stdin) {

        // read next int from stdin
        scanf("%d", &count);
        printf("int: %d\n", count);

        if (count > MAX_COUNT) {
            printf("Invalid count: %d.", count);
        } else {

            int array[count];

            for (int i = 0; i < count; i++) {
                scanf("%d", &array[i]);
            }
            scanf("%d", &target);

            int solution[count];
            reverse_sort();
            solution_count = solve();

            if (solution_count > 0) {
                for (int i = 0; i < solution_count; i++) {
                    printf("%d ", solution[i]);
                }
                printf("\n");
            } else {
                printf("Count = %d: no solution.", count);
            }
        }
        // newline thingy ???
    }
    

    printf("End of Processing.\n");
    return 0;
}
