#include <stdio.h>
#include <assert.h>
#include "orderedList.h"

#define MAX_WORD 100


int main( int argc, char *argv[] )
{
    printf("program: %s\nargc: %d\n\n", argv[0]+2, argc);

    List *concordance = construct();
    char word[MAX_WORD];
    int result;

    construct(concordance);

    while ( (result = scanf("%s", word)) != EOF )
    {
        if ( !find(concordance, word) )
        {
            insert(concordance, word);
        }
    }

    printf("Concordance:\n============================================================\n");
    print(concordance);
    printf("\n");

    printf("Size:\n============================================================\n");
    printf("%s\n\n", size(concordance));

    printf("Traversals:\n============================================================\n");
    printf("%d\n\n", traversals());

    destroy(concordance);

    printf("\nEnd of Program.\n");
    return 0;
}
