#include <stdio.h>
#include <stddef.h>

#include "ObjectManager.h"

// tracks the next reference (ID) to use, we start at 1 so we can use 0 as the NULL reference
static Ref nextRef = 1;

// A Memblock holds the relevent information associated with an allocated block of memory by our memory manager
typedef struct MEMBLOCK MemBlock;


// information needed to track our objects in memory
struct MEMBLOCK
{
  int numBytes;    // how big is this object?
  int startAddr;   // where the object starts
  Ref ref;         // the reference used to identify the object
  int count;       // the number of references to this object
  MemBlock *next;  // pointer to next block.  Blocks stored in a linked list.
};


// The blocks are stored in a linked list where the start of the list is pointed to by memBlockStart.
static MemBlock *memBlockStart;  // start of linked list of blocks allocated
static MemBlock *memBlockEnd;    // end of linked list of blocks allocated
static int numBlocks;            // number of blocks allocated

// our buffers. This is where we allocate memory from.  One of these is always the current buffer.  The other is used for swapping
// during compaction stage.

static unsigned char buffer1[MEMORY_SIZE];
static unsigned char buffer2[MEMORY_SIZE];

// points to the current buffer containing our data
static unsigned char *currBuffer = buffer1;

// points to the location of the next available memory location
static int freeIndex = 0;

// performs required setup
void initPool()
{
    numBlocks = 0;
    memBlockStart = NULL;
    memBlockEnd = NULL;
}

// performs required clean up
void destroyPool()
{
    //we want to delete all nodes from the linked list.
    while (memBlockStart != NULL)
    {
        memBlockEnd = memBlockStart->next;
        free(memBlockStart);
        memBlockStart = memBlockEnd;
    }
}

// Adds the given object into our buffer. It will fire the garbage collector as required.
// We always assume that an insert always creates a new object...
// On success it returns the reference number for the block allocated.
// On failure it returns NULL_REF (0)
Ref insertObject( const int size )
{
    // check if there is enough space for the new Object
    if (memBlockEnd->startAddr + memBlockEnd->numBytes + size > MEMORY_SIZE)
    {
        compact();  // garbage collect to make room for new Object
        if (memBlockEnd->startAddr + memBlockEnd->numBytes + size > MEMORY_SIZE)
        {
            // if there still isn't enough room, print error & return NULL_REF
            fprintf(stdout, "ERROR: Memory is full. Unable to add new Object.");
            return NULL_REF;
        }
    }

    // allocate space for next Node in Linked List
    MemBlock *memBlockNew = malloc(sizeof(MemBlock));

    // initalize info of the new MemBlock
    memBlockNew->numBytes = size;
    memBlockNew->startAddr = memBlockEnd->startAddr + memBlockEnd->numBytes;
    memBlockNew->ref = nextRef;
    memBlockNew->count = 1;
    memBlockNew->next = NULL;

    nextRef++;  // increment nextRef

    // add MemBlock to the end of the Linked List
    memBlockEnd->next = memBlockNew;
    memBlockEnd = memBlockEnd->next;
}

// returns a pointer to the object being requested
void *retrieveObject( const Ref ref )
{
    MemBlock *memBlockCurr = memBlockStart;

    while (memBlockCurr != NULL)
    {
        
        if (memBlockCurr->ref == ref)
        {
            return currBuffer[memBlockCurr->startAddr];
        }

        // check next Node in Linked List
        memBlockCurr = memBlockCurr->next;
    }

    // if ref could not be found, print error & return NULL_REF
    fprintf(stdout, "ERROR: Unable to locate Object with ref %d", ref);
    return NULL_REF;
}

// update our index to indicate that we have another reference to the given object
void addReference( const Ref ref )
{  
    MemBlock *memBlockCurr = memBlockStart;

    while (memBlockCurr != NULL)
    {
        if (memBlockCurr->ref == ref)
        {
            memBlockCurr->count++;  // increase count
            return;  // job done, return from function
        }
        
        // check next Node in Linked List
        memBlockCurr = memBlockCurr->next;
    }

    // if ref could not be found, print error
    fprintf(stdout, "ERROR: Unable to locate Object with ref %d", ref);
}

// update our index to indicate that a reference is gone
void dropReference( const Ref ref )
{  
    MemBlock *memBlockCurr = memBlockStart;
    MemBlock *memBlockPrev = memBlockStart;

    while (memBlockCurr != NULL)
    {
        if (memBlockCurr->ref == ref)
        {
            memBlockCurr->count--;  // increase count

            if (memBlockCurr->count == 0)
            {
                // delete object...
            }

            return;  // job done, return from function
        }

        // check next Node in Linked List
        memBlockCurr = memBlockCurr->next;
    }

    // if ref could not be found, print error
    fprintf(stdout, "ERROR: Unable to locate Object with ref %d", ref);
}

// performs our garbage collection
void compact()
{
    //write your code here
}

void dumpPool()
{
    //write your code here
}

//you may add additional function if needed