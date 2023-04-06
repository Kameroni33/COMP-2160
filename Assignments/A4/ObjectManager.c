#include "ObjectManager.h"
// You can add other header files if needed

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
}

// performs required clean up
void destroyPool()
{
    //we want to delete all nodes from the linked list.
    //write your code here


    free(buffer1);
    free(buffer2);
}

// Adds the given object into our buffer. It will fire the garbage collector as required.
// We always assume that an insert always creates a new object...
// On success it returns the reference number for the block allocated.
// On failure it returns NULL_REF (0)
Ref insertObject( const int size )
{
    
}

// returns a pointer to the object being requested
void *retrieveObject( const Ref ref )
{
    //write your code here
}

// update our index to indicate that we have another reference to the given object
void addReference( const Ref ref )
{  
    //write your code here
}

// update our index to indicate that a reference is gone
void dropReference( const Ref ref )
{  
    //write your code here
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