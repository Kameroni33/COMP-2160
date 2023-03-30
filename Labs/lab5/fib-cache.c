#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 40

long fib(int n, int cache[])
{
    long result;

    // check and see if the cache has the result we want
    if (n <= CACHE_SIZE && cache[n] >= 0)
        result = cache[n];

    // if cache doesn't have result, continue normally
    else {
        if (n == 0)
            result = 0;
        else if (n == 1 || n == 2)
            result = 1;
        else
            result = fib(n-1, cache) + fib(n-2, cache);
        
        // update cache if no entry exists yet
        if (n <= CACHE_SIZE && cache[n] == -1)
            cache[n] = result;
    }
    
    return result;
}

int main( int argc, char *argv[] )
{
    // we really should check the input...
    int fibNum = atoi(argv[1]);

    // create our 'cache' with all -1's initially
    int cache[CACHE_SIZE];

    for (int i = 0; i < CACHE_SIZE; i++){
        printf("%d\n", cache[i]);
    }

    printf("The %d Fibonacci number is %ld\n", fibNum, fib(fibNum, cache));

    for (int i = 0; i < CACHE_SIZE; i++){
        printf("%d ", cache[i]);
    }
    
    return EXIT_SUCCESS;
}
