#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "orderedList.h"

#define MAX_WORD 100

void removeChar(char *word, int index);

int main( int argc, char *argv[] )
{
    printf("program: %s\nargc: %d\n\n", argv[0]+2, argc);

    List *concordance = construct();
    char word[MAX_WORD];
    int result;

    construct(concordance);  // create concordance list

    // read each 'word' of the file
    while ( (result = scanf("%s", word)) != EOF )
    {
        // remove any whitespace or punctuation
        for (int i = 0; i < (int)strlen(word); i++)
        {
            word[i] = tolower(word[i]);  // make all characters lowercase to avoid duplicates

            if (isspace(word[i]) || ispunct(word[i]))
            {
                removeChar(word, i);  // remove the character if it is whitespace/punctuation
                i--;  // decrease index by 1 so we don't skip next character in word
            }
        }

        // add the word to the concordance (but not empty strings)
        if ( strlen(word) > 0 && !find(concordance, word) )
        {
            insert(concordance, word);  // add word to concordance if it isn't already
        }
    }

    // print index, list, size, and traversals
    print(concordance);
    printf("Size: %d\n", size(concordance));
    printf("Traversals: %d\n", traversals());

    destroy(concordance);  // clean up concordance list

    printf("\nEnd of Program.\n");
    return 0;
}

void removeChar(char *word, int index)
{
    assert(word != NULL);
    assert(index >= 0 && index < (int)strlen(word));

    // remove the char at 'index' by shifting the string in memory
    memmove(&word[index], &word[index + 1], strlen(word) - index);
}
