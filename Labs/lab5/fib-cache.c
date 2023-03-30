#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 42

long fib(int n)
{
    long result;
  
    if (n==0)
        result = 0;
    else if (n==1 || n==2)
        result = 1;
    else
        // first 
        result = fib(n-1) + fib(n-2);
  
    return result;
}

int main( int argc, char *argv[] )
{
    // we really should check the input...
    int fibNum = atoi(argv[1]);

    // instantiate our 'cache' with all 0's
    int cache[CACHE_SIZE] = {0};

    for (int i = 0; i < CACHE_SIZE; i++)
    {
        printf("%d\n", cache[i]);
    }
    
    printf("The %d Fibonacci number is %ld\n", fibNum, fib(fibNum));
    
    return EXIT_SUCCESS;
}
