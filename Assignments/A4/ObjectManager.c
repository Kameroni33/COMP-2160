#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "ObjectManager.h"

// tracks the next reference (ID) to use, we start at 1 so we can use 0 as the NULL reference
static Ref nextRef = 1;  // this value is never 'reset'. So theoretically a maximum of sizeof(unsigned long) values can be allocated

// A MemBlock holds the relevent information associated with an allocated block of memory by our memory manager
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
static int numBlocksCheck;  // for assert statements

// our buffers. This is where we allocate memory from.  One of these is always the current buffer.  The other is used for swapping
// during compaction stage.

static unsigned char buffer1[MEMORY_SIZE];
static unsigned char buffer2[MEMORY_SIZE];

// points to the current buffer containing our data
static unsigned char *currBuffer = buffer1;

// points to the location of the next available memory location
static int freeIndex = 0;
static int freeIndexCheck;  // for assert statements

// signatures for static methods
static void compact( void );
static Ref addMemBlock( const int size );
static void delMemBlock( MemBlock *delBlock, MemBlock *prevBlock );
static void checkState( void );

// initPool()
//  Perform required setup for our ObjectManager.
void initPool( void )
{
    // PRE-CONDITIONS:
    assert(memBlockStart == NULL);  // these values should already be
    assert(memBlockEnd == NULL);    // NULL/0 if proper clean up was
    assert(numBlocks == 0);         // performed (ie. destroyPool called)
    assert(freeIndex == 0);

    numBlocks = 0;  // initalize numBlocks
    freeIndex = 0;  // initalize freeIndex

    // Initialize our LinkedList to be EMPTY (ie. NULL pointers)
    memBlockStart = NULL;
    memBlockEnd = NULL;

    // POST-CONDITIONS
    checkState();
}

// destroyPool()
//  Perform required clean up for our ObjectManager.
void destroyPool( void )
{
    // PRE-CONDTIONS:
    checkState();

    // delete all Nodes from our LinkedList
    while (memBlockStart != NULL)
    {
        memBlockEnd = memBlockStart->next;
        free(memBlockStart);
        memBlockStart = memBlockEnd;
    }

    numBlocks = 0;  // reset numBlocks
    freeIndex = 0;  // reset freeIndex

    // POST-CONDITIONS:
    assert(memBlockStart == NULL);
    assert(memBlockEnd == NULL);
    assert(numBlocks == 0);
    assert(freeIndex == 0);
}

// insertObject()  
//  Adds the given object into our buffer. It will fire the garbage collector as required.
//  We always assume that an insert always creates a new object...
//  On success it returns the reference number for the block allocated.
//  On failure it returns NULL_REF (0)
Ref insertObject( const int size )
{
    // PRE-CONDITIONS:
    assert(size > 0 && size < MEMORY_SIZE);
    checkState();

    Ref result = NULL_REF;  // Ref of newly inserted Object or NULL_REF

    // check if there is enough space for the new Object
    if (memBlockEnd == NULL || memBlockEnd->startAddr + memBlockEnd->numBytes + size < MEMORY_SIZE)
    {
        result = addMemBlock(size);  // add new memBlock Node to LinkedList
    }

    else
    {
        compact();  // garbage collect to make room for new Object

        if (memBlockEnd->startAddr + memBlockEnd->numBytes + size < MEMORY_SIZE)
        {
            result = addMemBlock(size);  // add new memBlock Node to LinkedList
        }
        
        else
        {
            // if there still isn't enough room, print error
            fprintf(stderr, "ERROR: Memory is full. Unable to add new Object.\n");
        }
    }

    // POST-CONDITIONS:
    checkState();

    return result;
}

// retrieveObject()
//  Returns a pointer to the Object being requested.
//  If Object could not be found returns NULL_REF.
void *retrieveObject( const Ref ref )
{
    // PRE-CONDITIONS:
    assert(ref > 0 && ref < nextRef);
    checkState();

    void *objectPtr = NULL_REF;  // pointer to Object data
    int foundObject = 0;         // 'boolean' for if we have found the Object

    // temporary pointer for traversing LinkedList
    MemBlock *memBlockCurr = memBlockStart;

    while (memBlockCurr != NULL && !foundObject)
    {
        if (memBlockCurr->ref == ref)
        {
            // get pointer to the first index of the allocated buffer space
            objectPtr = &currBuffer[memBlockCurr->startAddr];
            foundObject = 1;
        }

        // check next Node in Linked List
        memBlockCurr = memBlockCurr->next;
    }

    if (!foundObject)
    {
        // if ref could not be found, print error
        fprintf(stderr, "ERROR: Unable to locate Object with ref %lu\n", ref);
    }

    // POST-CONDITIONS:
    checkState();

    return objectPtr;
}

// addReference()
//  Update our index to indicate that we have another reference to the given object
void addReference( const Ref ref )
{
    // PRE-CONDITIONS:
    assert(ref > 0 && ref < nextRef);
    checkState();

    int foundObject = 0;  // 'boolean' for if we have found the Object

    // temporary pointer for traversing LinkedList
    MemBlock *memBlockCurr = memBlockStart;

    while (memBlockCurr != NULL && !foundObject)
    {
        if (memBlockCurr->ref == ref)
        {
            memBlockCurr->count++;  // increase count
            foundObject = 1;
        }
        
        // check next Node in Linked List
        memBlockCurr = memBlockCurr->next;
    }

    if (!foundObject)
    {
        // if ref could not be found, print error
        fprintf(stderr, "ERROR: Unable to locate Object with ref %lu\n", ref);
    }

    // POST-CONDITIONS:
    checkState();
}

// update our index to indicate that a reference is gone
void dropReference( const Ref ref )
{
    // PRE-CONDITIONS:
    assert(ref > 0 && ref < nextRef);
    checkState();

    int foundObject = 0;  // 'boolean' for if we have found the Object

    // temporary pointers for traversing LinkedList
    MemBlock *memBlockCurr = memBlockStart;
    MemBlock *memBlockPrev = NULL;

    while (memBlockCurr != NULL && !foundObject)
    {
        if (memBlockCurr->ref == ref)
        {
            memBlockCurr->count--;  // decrease count
            foundObject = 1;

            if (memBlockCurr->count == 0)
            {
                // if reference count is now zero... delete object
                delMemBlock(memBlockCurr, memBlockPrev);
            }
        }

        // check next Node in Linked List
        memBlockPrev = memBlockCurr;
        memBlockCurr = memBlockCurr->next;
    }

    if (!foundObject)
    {
        // if ref could not be found, print error
        fprintf(stderr, "ERROR: Unable to locate Object with ref %lu\n", ref);
    }

    // POST-CONDITIONS:
    checkState();
}

// performs our garbage collection
static void compact( void )
{
    // PRE-CONDITIONS:
    freeIndexCheck = freeIndex;  // for POST-CONDITION comparison
    checkState();

    unsigned char *altBuffer;  // temporary pointer for currently unused buffer
    int altBufferIndex = 0;    // 'freeIndex' but for the altBuffer

    // temporary pointer for traversing LinkedList
    MemBlock *memBlockCurr = memBlockStart;

    if (currBuffer == buffer1)
    {
        altBuffer = buffer2;
    }
    
    else if (currBuffer == buffer2)
    {
        altBuffer = buffer1;
    }

    else
    {
        // should never reach this point
        fprintf(stderr, "ERROR: unexpected currBuffer during compact()");
        exit(1);
    }

    // go through LinkedList and compact memBlocks
    while (memBlockCurr != NULL)
    {
        assert(memBlockCurr->count != 0);  // sanity check

        // copy data from currBuffer -> altBuffer
        for (int i = 0; i < memBlockCurr->numBytes; i++)
        {
            altBuffer[altBufferIndex + i] = currBuffer[memBlockCurr->startAddr + i];
        }

        // update memBlock Entry
        memBlockCurr->startAddr = altBufferIndex;

        altBufferIndex += memBlockCurr->numBytes;

        // move to next Node in Linked List
        memBlockCurr = memBlockCurr->next;
    }

    printf("\nCOMPACTING BUFFER INFORMATION:\n\n");
    printf(" Num Objects: %d\n", numBlocks);
    printf(" Original Size: %d bytes\n", freeIndex);
    printf(" Compact Size: %d bytes\n", altBufferIndex);
    printf(" Reclaimed Mem: %d bytes\n", freeIndex - altBufferIndex);

    // swap currBuffer to altBuffer (compacted)
    currBuffer = altBuffer;
    // update freeIndex to reflect compacted buffer
    freeIndex = altBufferIndex;

    // POST-CONDITIONS
    assert(currBuffer == buffer1 || currBuffer == buffer2);
    assert(freeIndex <= freeIndexCheck);
    checkState();
}

void dumpPool( void )
{
    // PRE-CONDITIONS:
    checkState();

    int memorySize = MEMORY_SIZE;
    int allocatedMem = 0;  // calculate total 'alloacted' memory

    // temporary pointers for traversing LinkedList
    MemBlock *memBlockCurr = memBlockStart;

    printf("\nOBJECT MANAGER INFORMATION:\n\n");
    printf("  'Addr': Starting Address\n  'Refs': Reference Count\n\n");
    printf(" Number of Blocks: %d\n", numBlocks);
    printf(" Next free Index:  %d\n\n", freeIndex);

    while (memBlockCurr != NULL)
    {
        printf("  ID:   %lu\n", memBlockCurr->ref);
        printf("  Addr: %d\n", memBlockCurr->startAddr);
        printf("  Size: %d\n", memBlockCurr->numBytes);
        printf("  Refs: %d\n\n", memBlockCurr->count);

        allocatedMem += memBlockCurr->numBytes;

        // check next Node in Linked List
        memBlockCurr = memBlockCurr->next;
    }

    printf(" Buffer Size: %d\n  #: allocated memory (%d)\n  -: free memory (%d)\n\n[", memorySize, allocatedMem, memorySize - allocatedMem);

    for (int i = 0; i < 50; i++)
    {
        if (i < ((double)allocatedMem / memorySize) * 50)
        {
            printf("#");
        }
        
        else
        {
            printf("-");
        }
    }

    printf("] %.1f%% full\n\n", ((double)allocatedMem / memorySize) * 100);

    // POST-CONDITIONS:
    checkState();
}

// Additional Functions...

// addMemBlock()
//  add a new MemBlock to the end of the LinkedList.
static Ref addMemBlock( const int size )
{
    // PRE-CONDITIONS:
    assert(size > 0 && size < MEMORY_SIZE);

    // allocate space for next Node in Linked List
    MemBlock *memBlockNew = malloc(sizeof(MemBlock));

    // initalize info of the new MemBlock
    memBlockNew->numBytes = size;
    memBlockNew->startAddr = freeIndex;
    memBlockNew->ref = nextRef;
    memBlockNew->count = 1;
    memBlockNew->next = NULL;

    // if first Node in LinkedList
    if (memBlockStart == NULL && memBlockEnd == NULL)
    {
        memBlockStart = memBlockNew;
        memBlockEnd = memBlockNew;
    }

    else
    {
        // add MemBlock to the end of the Linked List
        memBlockEnd->next = memBlockNew;
        memBlockEnd = memBlockEnd->next;
    }

    numBlocks++;        // increment numBlocks
    nextRef++;          // increment nextRef
    freeIndex += size;  // update freeIndex

    // POST-CONDITIONS:
    checkState();

    return memBlockNew->ref;
}

// delMemBlock()
//  delete a MemBlock from the LinkedList
static void delMemBlock( MemBlock *delBlock, MemBlock *prevBlock )
{
    // PRE-CONDITIONS:
    assert(delBlock != NULL);

    if (prevBlock == NULL)
    {
        if (delBlock->next == NULL)
        {
            assert(memBlockStart->ref == delBlock->ref);
            assert(memBlockEnd->ref == delBlock->ref);

            // delete only Node in LinkedList
            memBlockStart = NULL;
            memBlockEnd = NULL;
        }

        else
        {
            assert(memBlockStart->ref == delBlock->ref);
            assert(memBlockEnd->ref != delBlock->ref);

            // delete first Node
            memBlockStart = memBlockStart->next;
        }
    }

    else
    {
        if (delBlock->next == NULL)
        {
            assert(memBlockStart->ref != delBlock->ref);
            assert(memBlockEnd->ref == delBlock->ref);
            
            // delete last Node
            prevBlock->next = NULL;
            memBlockEnd = prevBlock;
        }
        
        else
        {
            assert(memBlockStart->ref != delBlock->ref);
            assert(memBlockEnd->ref != delBlock->ref);

            // delete middle Node
            prevBlock->next = delBlock->next;
        }
    }

    numBlocks--;  // decrement numBlocks

    free(delBlock);  // free Node's allocated memory

    // POST-CONDITIONS
    checkState();
}

// checkState()
//  Invariance check function for Object Manager datastructures
static void checkState( void )
{
    MemBlock *memBlockCurr;
    numBlocksCheck = 0;
    freeIndexCheck = 0;

    // either the LinkedList is empty (NULL) or both pointers should be initialized (!NULL)
    assert( (memBlockStart == NULL && memBlockEnd == NULL) || (memBlockStart != NULL && memBlockEnd != NULL) );

    if (memBlockStart != NULL && memBlockEnd != NULL)
    {
        memBlockCurr = memBlockStart;

        while (memBlockCurr != NULL)
        {
            assert(memBlockCurr->numBytes > 0 && memBlockCurr->numBytes <= MEMORY_SIZE);
            assert(memBlockCurr->startAddr >= 0 && memBlockCurr->startAddr < MEMORY_SIZE);
            assert(memBlockCurr->count > 0);

            freeIndexCheck = (memBlockCurr->startAddr + memBlockCurr->numBytes) > freeIndexCheck ? (memBlockCurr->startAddr + memBlockCurr->numBytes) : freeIndexCheck;
            numBlocksCheck++;

            memBlockCurr = memBlockCurr->next;
        }
    }

    assert(numBlocksCheck == numBlocks);
    assert(freeIndexCheck <= freeIndex);  // can't account for deleted blocks
}
