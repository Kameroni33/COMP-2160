#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

    printf("argc: %d\nargv: %s\n", argc, argv[0]);

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
Cell makeCell(const int row, const int col);
Boolean equalCells(const Cell cell1, const Cell cell2);
Boolean validCell(const Cell theCell);


//////////////////////////////////////////////
// List routines
//////////////////////////////////////////////
Boolean noMoreCells();
Cell nextCell();
void addCell(const Cell cell);

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
            scanf("%d", &maze[i][j]);
        }
    }
}

Boolean solveMaze()
{
    Boolean result = false;
    printMaze();
    return result;

}

void checkState();
