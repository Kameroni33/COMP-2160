#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 100

long fib(int n, long long cache[])
{
    long long result;

    // check and see if the cache has the result we want
    if (n < CACHE_SIZE && cache[n] != -1)
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
        if (n < CACHE_SIZE)
            cache[n] = result;
    }
    
    return result;
}

int main( int argc, char *argv[] )
{
    // we really should check the input...
    int fibNum = atoi(argv[1]);

    // create our 'cache' with all -1's initially
    long long cache[CACHE_SIZE];

    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i] = -1;
    }

    printf("The %d Fibonacci number is %ld\n", fibNum, fib(fibNum, cache));

    // Print Cache
    // for (int i = 0; i < CACHE_SIZE; i++){
    //     printf("%lld ", cache[i]);
    // }
    
    return EXIT_SUCCESS;
}
