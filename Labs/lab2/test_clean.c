#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define MAX_STRING 100

// Write your clean function here

void test(char tester[], char target[])
{
   char cleaned[MAX_STRING];
   int result;

   printf("testing: %s\n", tester);
   result = clean(tester, cleaned);
   assert(result == strlen(target));
   assert(result == strlen(cleaned));
   assert(strcmp(cleaned, target) == 0);
}

int main()
{
   test("hello", "hello");
   test("hello world", "hello world");
   test("isn't", "isn't");
   test("Hello", "hello");
   test("C3PO", "c3po");
   test("hello world!", "hello world");
   test("C3P0", "c3p");
   test("\"hello world\"", "hello world");
   test("\"Hello, World\", she said.", "hello, world\", she said");
   test("  Hello world  ", "hello world");
   test("`~!@#$%^&*()_+ :;',./<>?_-+=\t\n1234567890hello world0987654321\t\n=+-_?></.,';: +_)(*&^%$#@!~`", "hello world");
   test("", "");
   test("!", "");
   test("&@@>%^#", "");
   
   printf("\nSuccessful end of tests.\n");
   
   return EXIT_SUCCESS;
}