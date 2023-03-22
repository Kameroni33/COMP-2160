#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INDEX_SIZE 256

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
};

static int total_num_traversals = 0;

// construct a linked list
List *construct( )
{
    List *list;

    list = malloc( sizeof( List ) );
    list->top = NULL;

    for (int i = 0; i < INDEX_SIZE; i++)
    {
        list->index[i] = NULL;
    }

    return list;
}

// perform an ordered insertion of an item into a list
boolean insert( List *list, char *new_string )
{
    // Pre-Conditions =================================================================
    assert(list != NULL);
    assert(new_string != NULL);
    // ================================================================================

    boolean rc = true;
    Node *newNode = NULL;
    Node *curr;
    Node *prev;
    int startIndex;

    newNode = malloc( sizeof( Node ) );
    newNode->string = new_string;

    // determine first node based on index
    printf("first char: '%c' %d\n", new_string[0], new_string[0]);

    // determine first node based on index list
    startIndex = new_string[0];
    while ( (curr = list->index[startIndex]) == NULL && !(strcmp( curr->string, new_string ) >= 0) )
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

    if ( prev == NULL )
    {
        // Case 1: prev Node is NULL due to us being at the head of the list
        if (startIndex == 0)
        {
            // update list top Node
            newNode->next = list->top;
            list->top = newNode;
        }
        
    } else {
        newNode->next = curr;
        prev->next = newNode;
    }

    // note that we need to have space for the string as well!
    newNode->string = malloc( strlen( new_string ) + 1 );
    strcpy( newNode->string, new_string );

    return rc;
}

// tells us whether or not the given string is in the list
boolean find( List *list, char *target )
{
    boolean found = false;
    int compare;
    Node *curr = list->top;

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

    return found;
}

// calculates the number of nodes in a list
int node_count( List *list )
{
    int count;
    Node *curr = list->top;

    count = 0;
    while ( NULL != curr )
    {
        count++;
        curr = curr->next;
    }

    return count;
}

// calculates the size of a list
int size( List *list )
{
    return node_count( list );
}

// print the contents of a list, one item per line
void print( List *list )
{
    Node *curr = list->top;

    while ( NULL != curr )
    {
        printf( "%s\n", curr->string );
        curr = curr->next;
    }
}

// returns the total number of items traversed in the list
int traversals( )
{
    return total_num_traversals;
}

// destroy the nodes in a list
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
