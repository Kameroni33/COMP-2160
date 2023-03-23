#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INDEX_SIZE 256

// ====================================================================================
// STRUCTS & TYPEDEFS
// ====================================================================================

typedef enum BOOL { false, true } boolean;

// Linked list node definition
typedef struct NODE Node;

struct NODE
{
    char *string;
    Node *next;
};

typedef struct LIST List;

struct LIST
{
    Node *top;
    Node *index[INDEX_SIZE];
    int nodeCount;
};

// ====================================================================================
// GLOBAL VARIABLES & PROTOTYPES
// ====================================================================================

static int total_num_traversals = 0;

static void validateList(List *list);  // invariant function

// ====================================================================================
// FUNCTION IMPLEMENTATIONS
// ====================================================================================

// --------------------------------------------------------------------
// construct a linked list
// --------------------------------------------------------------------
List *construct( )
{
    List *list;

    list = malloc( sizeof( List ) );
    list->top = NULL;
    list->nodeCount = 0;

    for (int i = 0; i < INDEX_SIZE; i++)
    {
        list->index[i] = NULL;
    }

    // Post-Conditions:
    validateList(list);

    return list;
}

// --------------------------------------------------------------------
// perform an ordered insertion of an item into a list
// --------------------------------------------------------------------
boolean insert( List *list, char *new_string )
{
    // Pre-Conditions:
    assert(list != NULL);
    assert(new_string != NULL);

    boolean rc = true;
    Node *newNode = NULL;
    Node *curr;
    Node *prev;
    int startIndex;

    newNode = malloc( sizeof( Node ) );
    newNode->string = new_string;

    // determine curr Node based on index array (or next closest node)
    // Note: if new_string needs to go before curr Node, go at least 1 more index back so we can find prev Node
    startIndex = new_string[0];
    while ( (curr = list->index[startIndex]) == NULL || !(strcmp( curr->string, new_string ) < 0) )
    {
        if (startIndex == 0)
        {
            curr = list->top;
            break;
        }
        startIndex--;
    }

    prev = NULL;
    while ( NULL != curr && strcmp( curr->string, new_string ) < 0 )
    {
        prev = curr;
        total_num_traversals++;
        curr = curr->next;
    }

    if ( prev == NULL )  // list top Node
    {
        assert(startIndex == 0);

        // update list
        newNode->next = list->top;
        list->top = newNode;

        // update index
        list->index[(int)new_string[0]] = newNode;
    }
    else  // mid-list Node
    {
        // update list
        newNode->next = curr;
        prev->next = newNode;

        // update index
        if ( list->index[(int)new_string[0]] == NULL || ( curr != NULL && strcmp(list->index[(int)new_string[0]]->string, curr->string) == 0 ) )
        {
            list->index[(int)new_string[0]] = newNode;
        }
    }

    // note that we need to have space for the string as well!
    newNode->string = malloc( strlen( new_string ) + 1 );
    strcpy( newNode->string, new_string );

    // update node count
    list->nodeCount++;

    // Post-Conditions:
    validateList(list);

    return rc;
}

// --------------------------------------------------------------------
// tells us whether or not the given string is in the list
// --------------------------------------------------------------------
boolean find( List *list, char *target )
{
    // Pre-Conditions:
    assert(list != NULL);
    assert(target != NULL);

    boolean found = false;
    Node *curr;
    int compare;

    // determine curr Node based on index array
    // Note: if no index exists, we can assume the target string isn't in the list
    if ( (curr = list->index[(int)target[0]]) != NULL )
    {
        while ( NULL != curr && !found )
        {
            compare = strcmp( target, curr->string );
            // printf("[%s == %s -> %d]", target, curr->string, compare);  // debug
            if ( compare == 0 ) {
                found = true;
            } else if (compare < 0) {
                // gone too far
                curr = NULL;
            } else {
                total_num_traversals++;
                curr = curr->next;
            }
        }
    }

    // Post-Conditions:
    validateList(list);
    
    return found;
}

// --------------------------------------------------------------------
// calculates the size of a list
// --------------------------------------------------------------------
int size( List *list )
{
    return list->nodeCount;
}

// --------------------------------------------------------------------
// print the contents of a list, one item per line
// --------------------------------------------------------------------
void print( List *list )
{
    // Pre-Conditions:
    assert(list != NULL);

    Node *curr = list->top;

    // print index
    printf("Index:\n");
    for (int i = 0; i < INDEX_SIZE; i++)
    {
        if(list->index[i] != NULL)
        {
            printf( "%d | '%c' | %s\n", i, i, list->index[i]->string );
        }
    }

    // print list
    printf("List:\n");
    while ( NULL != curr )
    {
        printf( "%s\n", curr->string );
        curr = curr->next;
    }

    // Post-Conditions:
    validateList(list);
}

// --------------------------------------------------------------------
// returns the total number of items traversed in the list
// --------------------------------------------------------------------
int traversals( )
{
    return total_num_traversals;
}

// --------------------------------------------------------------------
// destroy the nodes in a list
// --------------------------------------------------------------------
void destroy( List *list )
{
    Node *curr = list->top;
    Node *next;

    while ( NULL != curr ) {
        next = curr->next;
        free( curr->string );
        free( curr );
        curr = next;
    }
    
    free( list );
}

// --------------------------------------------------------------------
// assert that the current state of list is valid
// --------------------------------------------------------------------
void validateList(List *list)
{
    assert(list != NULL);
}
