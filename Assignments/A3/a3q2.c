#include <stdio.h>
#include <assert.h>
#include "orderedList.h"

#define MAX_WORD 20

//=====================================================================================
// Global Variables
//=====================================================================================
static int testsTotal;
static int testsPassed;
static int testsFailed;
static int lastTraversals;

//=====================================================================================
// Function Prototypes
//=====================================================================================
void testOrderedList(char *words[], int numWords, int expectedInsertTraversals, int expectedFindTraversals);

//=====================================================================================
// Function Definitions
//=====================================================================================
int main( int argc, char *argv[] )
{
    printf("program: %s\nargc: %d\n\n", argv[0]+2, argc);

    List *concordance = construct();
    char word[MAX_WORD];
    int result;

    construct(concordance);

    while ( (result = scanf("%s", word)) != EOF )
    {
        printf("%s\n", word);
    }

    print(concordance);

    destroy(concordance);

    printf("\nEnd of Program.\n");
    return 0;
}
