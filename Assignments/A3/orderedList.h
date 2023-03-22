#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum BOOL { false, true } boolean;
// typedef struct NODE Node;
typedef struct LIST List;

List *construct( );
boolean insert( List *list, char *new_string );
boolean find( List *list, char *target );
int node_count( List *list );
int size( List *list );
void print( List *list );
int traversals( );
void destroy( List *list );
