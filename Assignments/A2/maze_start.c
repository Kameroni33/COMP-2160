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

// get the char at position of cell
char getCellValue(const Cell cell);
// set the value at the position of cell to be char
void setCellValue(const Cell cell, const char value);

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
    // for each row of maze
    for (int i = 0; i < mazeRows; i++)
    {
        // for each column in row
        for (int j = 0; j < mazeCols; j++)
        {
            // print the char located at the current [row][col]
            printf("%c ", maze[i][j]);
        }
        
        // print a new line at the end of each row
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
        }
    }

    printf("\n");
}

char getCellValue(const Cell cell)
{
    return maze[cell.row][cell.column];
}

void setCellValue(const Cell cell, const char value)
{
    maze[cell.row][cell.column] = value;
}

void addNeighbours(const Cell cell)
{
    // NORTH neighbour
    if (cell.row > 0)
    {
        Cell north = makeCell(cell.row-1, cell.column);
        if (getCellValue(north) == SPACE)
        {
            addCell(north);
        }
    }

    // EAST neighbour
    if (cell.column < mazeCols-1)
    {
        Cell east = makeCell(cell.row, cell.column+1);
        if (getCellValue(east) == SPACE)
        {
            addCell(east);
        }
    }

    // SOUTH neighbour
    if (cell.row < mazeRows-1)
    {
        Cell south = makeCell(cell.row+1, cell.column);
        if (getCellValue(south) == SPACE)
        {
            addCell(south);
        }
    }

    // WEST neighbour
    if (cell.column > 0)
    {
        Cell east = makeCell(cell.row, cell.column-1);
        if (getCellValue(east) == SPACE)
        {
            addCell(east);
        }
    }
}


Boolean solveMaze()
{
    Cell currentCell = mouse;

    while (equalCells(currentCell, escape))
    {
        // mark current cell as visited
        setCellValue(currentCell, VISITED);
        // add the unvisted open neighbours of current cell to list
        addNeighbours(currentCell);

        if (noMoreCells)
        {
            // there are no more cells to check, thus we are trapped
            return false;
        }

        else
        {
            // check the next cell in our list of cells
            currentCell = nextCell();
        }

        // print out the current state of the maze
        printMaze();
        printf("\n");
    }

    // if we reach this point (ie. break out of while loop)
    // then we've reached the escape and the mouse is free!
    return true;
}

void checkState();
