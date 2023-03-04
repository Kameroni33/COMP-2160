#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>  // for use of isspace() function

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

#define MAX_DIMENSION 20

// constant definitions for the different cell states
const char WALL    = '1';
const char SPACE   = '0';
const char VISITED = '.';
const char MOUSE   = 'm';
const char EXIT    = 'e';

typedef enum BOOL { false, true } Boolean;

struct CELL
{
  int row;
  int column;
};
typedef struct CELL Cell;

typedef struct CELL_NODE CellNode;
struct CELL_NODE
{
  Cell     cell;
  CellNode *next;
};

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

CellNode *top = NULL;

// a 2D array used to store the maze
char maze[MAX_DIMENSION][MAX_DIMENSION];
int mazeRows;
int mazeCols;

// holds the location of the mouse and escape hatch
Cell mouse;
Cell escape;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

// basic cell manipulation

// returns true if the cells are at the same position in our maze
Boolean equalCells(const Cell cell1, const Cell cell2);
// returns a new cell object
Cell makeCell(const int row, const int col);
// returns true if the cell is within our maze
Boolean validCell(const Cell theCell);

// routines for managing our backtracking

// returns true if there are no more cells to try
Boolean noMoreCells();
// returns the next cell to try for a path out of the maze
Cell nextCell();
// introduces a new cell to try
void addCell(const Cell cell);

void printMaze();
void loadMaze();

// returns true if there's a solution to the maze
Boolean solveMaze();

// our invariant checker
void checkState();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

int main( int argc, char *argv[] )
{

    printf("argc: %d\nargv: %s\n\n", argc, argv[0]);

    loadMaze();

    if ( solveMaze() )
    {
        printf( "The mouse is free!!!!\n" );
    }
    
    else
    {
        printf( "The mouse is trapped!!!!\n" );
    }
    
    printf( "\nEnd of processing\n" );
    
    return EXIT_SUCCESS;
}


//////////////////////////////////////////////
// Cell routines
//////////////////////////////////////////////

Boolean equalCells(const Cell cell1, const Cell cell2)
{
    // check if the rows & cloumns match, and return the result as a Boolean
    return (Boolean)(cell1.row == cell2.row && cell1.column == cell2.column);
}

Cell makeCell(const int row, const int col)
{
    // create a new cell with the given row and col
    Cell newCell = {row, col};
    return newCell;
}

Boolean validCell(const Cell theCell)
{
    // check that the cell's row & column are both greater than zero and less than maxeRows and mazeCols respectively
    return (Boolean)(theCell.row >= 0 && theCell.row < mazeRows && theCell.column >= 0 && theCell.column < mazeCols);
}


//////////////////////////////////////////////
// List routines
//////////////////////////////////////////////

Boolean noMoreCells()
{
    return (Boolean)(top->next == NULL);
}

Cell nextCell()
{
    Cell nextCell = {0};  // returns an empty cell (ie. row = 0, col = 0) if there is no next cell

    if (!noMoreCells())
    {
        // get the next cell value from the node
        nextCell = top->cell;

        // unlink top node from list
        CellNode *oldNode = top;  // make a copy of the top pointer
        top = top->next;          // resign the top pointer to be the next in the list
        free(oldNode);            // free the 'old' top value
    }

    else
    {
        printf("tried to get next Cell but list is empty\n");
    }

    return nextCell;
}

void addCell(const Cell cell)
{
    // allocate space for the new node
    CellNode *newCellNode = malloc(sizeof(CellNode));
    // set the values of the newCellNode
    newCellNode->cell = cell;
    newCellNode->next = top;
    // set the newCellNode as the new top
    top = newCellNode;
}

//////////////////////////////////////////////
// Maze routines
//////////////////////////////////////////////

void printMaze()
{
    for (int i = 0; i < mazeRows; i++)
    {
        for (int j = 0; j < mazeCols; j++)
        {
            printf("%c ", maze[i][j]);
        }
        
        printf("\n");
    }

    // // TESTING LINKED LIST
    // for (int i = 0; i < (mazeRows * mazeCols); i++)
    // {
    //     Cell currCell = nextCell();
    //     printf("List (%02d): [%d, %d]", i, currCell.row, currCell.column);
    // }
}

void loadMaze()
{
    // read the maze width and height from first line of file
    scanf("%d", &mazeRows);
    scanf("%d", &mazeCols);
    printf("Rows: %d\nCols: %d\n", mazeRows, mazeCols);

    // read in the values for the maze
    for (int i = 0; i < mazeRows; i++)
    {
        for (int j = 0; j < mazeCols; j++)
        {
            // read next cell value into maze array (ignoring whitespace and newlines)
            while (isspace(maze[i][j] = getchar()));
            // printf("[%d, %d]: %c\n", i, j, maze[i][j]);
            
            // check if cell is the MOUSE
            if (maze[i][j] == MOUSE)
            {
                mouse.row = i;
                mouse.column = j;

                // printf("> mouse at  (%d, %d)\n", i, j);
            }

            // check if cell is the EXIT
            if (maze[i][j] == EXIT)
            {
                escape.row = i;
                escape.column = j;

                // printf("> escape at (%d, %d)\n", i, j);
            }

            // TESTING LINKED LIST


            printf("cell: %d, %d\n", makeCell(i, j).row, makeCell(i, j).column);
            addCell(makeCell(i, j));
        }
    }

    printf("\n");
}

Boolean solveMaze()
{
    Boolean result = false;
    printMaze();
    return result;

}

void checkState();
