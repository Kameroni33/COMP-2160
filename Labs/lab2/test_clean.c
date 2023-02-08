#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define MAX_STRING 100


int clean(char dirty[], char cleaned[]) {
   // keep track our our current position in both string arrays
   int pos_d  = 0;
   int pos_c  = 0;
   int length = 0;
   // iterate through the dirty string and copy values into the cleaned string
   while (dirty[pos_d] != '\0') {
      // check if character is alphanumeric (function isalnum() returns a positive int if alphanumeric, otherwise 0)
      if (isalnum(dirty[pos_d]) != 0) {
         // clean current character and copy it into the cleaned string
         cleaned[pos_c] = tolower(dirty[pos_d]);
         pos_c++;
         length++;
      }
      pos_d++;
   }
   // null-terminate our cleaned string
   cleaned[pos_c] = '\0';
   //return our calculated length of the cleaned string
   return length;
}

void test(char tester[], char target[])
{
   char cleaned[MAX_STRING];
   int result;

   printf("testing: %s\n", tester);
   result = clean(tester, cleaned);

   // testing start
   printf("cleaned:       '%s'\n", cleaned);
   printf("length result:  %lu\n", strlen(result));
   printf("length target:  %lu\n", strlen(target));
   printf("length cleaned: %lu\n", strlen(cleaned));
   printf("result:         %d\n", strcmp(cleaned, target));
   // testing end

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