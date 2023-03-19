#include <stdio.h>
#include <assert.h>
#include "orderedList.h"

//=====================================================================================
// Global Variables & Structs
//=====================================================================================
static int testsTotal;
static int testsPassed;
static int testsFailed;

typedef enum BOOL { false, true } boolean;

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

    testOrderedList();

    printf("testsTotal:  %d\n", testsTotal);
    printf("testsPassed: %d\n", testsPassed);
    printf("testsFailed: %d\n", testsFailed);

    printf("\nEnd of Program.\n");
    return 0;
}

void testOrderedList()
{
    testsTotal++;
}
