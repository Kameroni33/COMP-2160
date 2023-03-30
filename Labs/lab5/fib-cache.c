#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 42

long fib(int n, int cache[])
{
    long result;
  
    if (n==0)
        result = 0;
    else if (n==1 || n==2)
        result = 1;
    else
        if (cache[n] > 0)
            result = cache[n];  // first check the cache
        else
            result = fib(n-1, cache) + fib(n-2, cache);  // if cache doesn't have result, continue recursion
  
    return result;
}

int main( int argc, char *argv[] )
{
    // we really should check the input...
    int fibNum = atoi(argv[1]);

    // create our 'cache' with all 0's initially
    int cache[CACHE_SIZE] = {0};

    printf("The %d Fibonacci number is %ld\n", fibNum, fib(fibNum, cache));
    
    return EXIT_SUCCESS;
}
