#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>  // for use of isspace() function
#include <string.h>  // for use of strcmp() function

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
// prints contents of node (for debugging)
void printTop();

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
    // printf("argc: %d\nargv: %s\n\n", argc, argv[0]);  // debug log

    // Pre-Conditions =================================================================
    assert(argc == 1);                       // there should only be a single arg (ie. './maze')
    assert(strcmp(argv[0], "./maze") == 0);  // strcmp() returns 0 on success
    // ================================================================================

    loadMaze();  // load the maze into our array

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
    // printf("Comparing cells [%d, %d] and [%d, %d]: %d\n", cell1.row, cell1.column, cell2.row, cell2.column, (cell1.row == cell2.row && cell1.column == cell2.column));  // debug log

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
    Boolean validDimensions = (Boolean)(theCell.row >= 0 && theCell.row < mazeRows && theCell.column >= 0 && theCell.column < mazeCols);
    // check that the cell is a valid character in the maze
    Boolean validCharacter = (Boolean)(
        maze[theCell.row][theCell.column] == WALL ||
        maze[theCell.row][theCell.column] == SPACE ||
        maze[theCell.row][theCell.column] == VISITED ||
        maze[theCell.row][theCell.column] == MOUSE ||
        maze[theCell.row][theCell.column] == EXIT
    );
    return (validDimensions && validCharacter);
}

//////////////////////////////////////////////
// List routines
//////////////////////////////////////////////

Boolean noMoreCells()
{
    // printf("Checking if list is empty: %d\n", (top == NULL));  // debug log
    // printNode(top);  // debug log

    // check if our current top is NULL (if it is that means our list is empty)
    return (Boolean)(top == NULL);
}

Cell nextCell()
{
    // Pre-Conditions =================================================================
    assert(!noMoreCells());  // check that there are still Cells in our NodeList
    // ================================================================================

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
        printf("Error: tried to get next Cell but list is empty...\n");
    }

    // Post-Conditions =================================================================
    checkState();  // check valid NodeList
    // ================================================================================

    return nextCell;
}

void addCell(const Cell cell)
{
    // Pre-Conditions =================================================================
    assert(validCell(cell));  // check for valid Cell
    // ================================================================================

    // allocate space for the new node
    CellNode *newCellNode = malloc(sizeof(CellNode));
    // set the values of the newCellNode
    newCellNode->cell = cell;  // set our new node to have the passed in cell value
    newCellNode->next = top;   // existing top now becomes the 'second' node in list
    // set the newCellNode as the new top
    top = newCellNode;

    // Post-Conditions ================================================================
    assert(equalCells(top->cell, cell));  // check that top->cell is what we expect
    checkState();  // check valid NodeList
    // ================================================================================
}

void printTop()
{
    printf("Top contents: [%d, %d]\n", top->cell.row, top->cell.column);
    printf("Next node: %p\n", (void *)(top->next));
}

//////////////////////////////////////////////
// Maze routines
//////////////////////////////////////////////

void printMaze()
{
    // Pre-Conditions =================================================================
    assert(maze != NULL);  // check that maze array isn't NULL
    checkState();          // validate current state of maze

    assert(mazeRows >= 0 && mazeRows <= MAX_DIMENSION);  // ensure valid dimenstions
    assert(mazeCols >= 0 && mazeCols <= MAX_DIMENSION);  // ensure valid dimenstions
    // ================================================================================

    // for each row of maze
    for (int i = 0; i < mazeRows; i++)
    {
        // for each column in row
        for (int j = 0; j < mazeCols; j++)
        {
            // Ensure maze[i][j] is a valid character =================================
            assert(maze[i][j] == WALL || maze[i][j] == SPACE || maze[i][j] == VISITED || maze[i][j] == MOUSE || maze[i][j] == EXIT);
            // ========================================================================

            // print the char located at the current [row][col]
            printf("%c ", maze[i][j]);
        }
        
        // print a new line at the end of each row
        printf("\n");
    }

    // Post-Conditions ================================================================
    checkState();  // validate current state of maze
    // ================================================================================
}

void loadMaze()
{
    // read the maze width and height from first line of file
    scanf("%d", &mazeRows);
    scanf("%d", &mazeCols);

    // Pre-Conditions =================================================================
    assert(maze != NULL);  // check that maze array isn't NULL

    assert(mazeRows >= 0 && mazeRows <= MAX_DIMENSION);  // ensure valid dimenstions
    assert(mazeCols >= 0 && mazeCols <= MAX_DIMENSION);  // ensure valid dimenstions
    // ================================================================================

    // printf("Rows: %d\nCols: %d\n", mazeRows, mazeCols);  // debug log

    // read in the values for the maze
    for (int i = 0; i < mazeRows; i++)
    {
        for (int j = 0; j < mazeCols; j++)
        {
            // read next cell value into maze array (ignoring whitespace and newlines)
            while (isspace(maze[i][j] = getchar()));

            // Assert valid character =================================================
            assert(maze[i][j] == WALL || maze[i][j] == SPACE || maze[i][j] == VISITED || maze[i][j] == MOUSE || maze[i][j] == EXIT);
            // ========================================================================
            // printf("[%d, %d]: %c\n", i, j, maze[i][j]);  // debug log 
            
            // check if cell is the MOUSE
            if (maze[i][j] == MOUSE)
            {
                mouse.row = i;
                mouse.column = j;

                // printf("found mouse at (%d, %d)\n", i, j);  // debug log
            }

            // check if cell is the EXIT
            if (maze[i][j] == EXIT)
            {
                escape.row = i;
                escape.column = j;

                // printf("found escape at (%d, %d)\n", i, j);  // debug log
            }
        }
    }

    // Post-Conditions ================================================================
    checkState();  // check that the initial state of the maze is valid

    assert(maze[mouse.row][mouse.column] == MOUSE);
    assert(maze[escape.row][escape.column] == EXIT);
    // ================================================================================

    // print out the initial state of the maze
    printMaze();
    printf("\n");
}

char getCellValue(const Cell cell)
{
    // Pre-Conditions =================================================================
    assert(cell.row >= 0 && cell.row < mazeRows);        // check valid Cell row
    assert(cell.column >= 0 && cell.column < mazeCols);  // check valid Cell col
    // ================================================================================
    return maze[cell.row][cell.column];
}

void setCellValue(const Cell cell, const char value)
{
    // Pre-Conditions =================================================================
    assert(cell.row >= 0 && cell.row < mazeRows);        // check valid Cell row
    assert(cell.column >= 0 && cell.column < mazeCols);  // check valid Cell col
    // check valid character
    assert(value == WALL || value == SPACE || value == VISITED || value == MOUSE || value == EXIT);
    // ================================================================================
    maze[cell.row][cell.column] = value;
}

void addNeighbours(const Cell cell)
{
    // printf("adding neighours of cell [%d, %d] to list\n", cell.row, cell.column);  // debug log

    // NORTH neighbour
    if (cell.row > 0)
    {
        // printf("checking NORTH neighbour...\n");  // debug log
        Cell north = makeCell(cell.row-1, cell.column);
        if (getCellValue(north) == SPACE || getCellValue(north) == EXIT)
        {
            addCell(north);

            // printf("found open cell at [%d, %d]\n", north.row, north.column);  // debug log
        }
    }

    // EAST neighbour
    if (cell.column < mazeCols-1)
    {
        // printf("checking EAST neighbour...\n");  // debug log

        Cell east = makeCell(cell.row, cell.column+1);
        if (getCellValue(east) == SPACE || getCellValue(east) == EXIT)
        {
            addCell(east);

            // printf("found open cell at [%d, %d]\n", east.row, east.column);  // debug log
        }
    }

    // SOUTH neighbour
    if (cell.row < mazeRows-1)
    {
        // printf("checking SOUTH neighbour...\n");  // debug log

        Cell south = makeCell(cell.row+1, cell.column);
        if (getCellValue(south) == SPACE || getCellValue(south) == EXIT)
        {
            addCell(south);

            // printf("found open cell at [%d, %d]\n", south.row, south.column);  // debug log
        }
    }

    // WEST neighbour
    if (cell.column > 0)
    {
        // printf("checking WEST neighbour...\n");  // debug log

        Cell east = makeCell(cell.row, cell.column-1);
        if (getCellValue(east) == SPACE || getCellValue(east) == EXIT)
        {
            addCell(east);

            // printf("found open cell at [%d, %d]\n", east.row, east.column);  // debug log
        }
    }
}


Boolean solveMaze()
{
    // Pre-Conditions (1) =============================================================
    checkState();  // check that the initial state of the maze is valid

    // the mouse Cell should not be overwritten at this point
    assert(maze[mouse.row][mouse.column] == MOUSE);
    // ================================================================================

    Cell currentCell = mouse;
    // int step = 0;  // for debug logging

    // Pre-Conditions (2) =============================================================
    assert(equalCells(currentCell, mouse));
    // ================================================================================

    while (!equalCells(currentCell, escape))
    {
        // printf("Step: %d\n", step++);  // debug log
        checkState();

        // mark current cell as visited
        setCellValue(currentCell, VISITED);
        // add the unvisted open neighbours of current cell to list
        addNeighbours(currentCell);

        // print out the current state of the maze
        printMaze();
        printf("\n");

        if (noMoreCells())
        {
            // Post-Condition (1) =====================================================
            assert(noMoreCells());                       // check that the list is empty
            assert(!equalCells(currentCell, escape));  // check current cell is not the escape
            // ========================================================================

            // there are no more cells to check, thus we are trapped
            return false;
        }

        else
        {
            // check the next cell in our list of cells
            currentCell = nextCell();
        }
    }

    // Post-Condition (2) =============================================================
    assert(equalCells(currentCell, escape));  // check that the current cell is the escape
    // ================================================================================

    // if we reach this point (ie. break out of while loop)
    // then we've reached the escape and the mouse is free!
    return true;
}

void checkState()
{
    // validate Maze ==================================================================
    assert(maze != NULL);  // check that maze array isn't NULL 
    for (int i = 0; i < mazeRows; i++)
    {
        for (int j = 0; j < mazeCols; j++)
        {
            // valid each cell
            assert(validCell(makeCell(i, j)));

            // check edges are all '1'
            if ( i == 0 || i == mazeRows-1 || j == 0 || j == mazeCols-1)
            {
                assert(maze[i][j] == WALL);
            }
        }
    }

    // validate special Cells =========================================================
    assert(mouse.row > 0 && mouse.row < mazeRows-1);          // assert mouse has a valid row
    assert(mouse.column > 0 && mouse.column < mazeCols-1);    // assert mouse has a valid col
    assert(escape.row > 0 && escape.row < mazeRows-1);        // assert escape has a valid row
    assert(escape.column > 0 && escape.column < mazeCols-1);  // assert escape has a valid col

    // the mouse Cell may have been overwritten with a '.' but escape should always be 'e'
    assert(maze[escape.row][escape.column] == EXIT);

    // validate NodeList ==============================================================
    CellNode *tempCellNode = top;  // local copy of top
    while (tempCellNode != NULL)   // iterate through CellNode list and make sure all Cells are valid
    {
        // check that the cell is valid
        assert(validCell(tempCellNode->cell));
        // check next cell
        tempCellNode = tempCellNode->next;
    }
}
