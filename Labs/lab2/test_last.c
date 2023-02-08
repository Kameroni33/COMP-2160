#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


char last_non_quote_character(char* quote) {

   // keep track of current position in string and last character
   int pos = 0;
   char last_char = '\0';

   // iterate through string (ie. until current character is '\0')
   while(quote[pos] != '\0') {

      // check if the current character is a '\"', and update our last_char if it isn't
      if (quote[pos] != '\"') {
         last_char = quote[pos];
      }

      pos++;
   }

   // return the last character we found, or '\0' if none were found
   return last_char;
}


int main()
{
   printf("====================\n\n");

   printf("testing: hello world\n");
   assert(last_non_quote_character("hello world") == 'd');
   printf("testing: quote\"\n");
   assert(last_non_quote_character("quote\"") == 'e');
   printf("testing: quot\"e\n");
   assert(last_non_quote_character("quot\"e") == 'e');
   printf("testing: space before quote \"\n");
   assert(last_non_quote_character("space before quote \"") == ' ');
   printf("testing: space after quote\" \n");
   assert(last_non_quote_character("space after quote\" ") == ' ');
   printf("testing: early\"quote mark\"\n");
   assert(last_non_quote_character("early\"quote mark\"") == 'k');
   printf("testing: two quotes\"\"\n");
   assert(last_non_quote_character("two quotes\"\"") == 's');
   printf("testing: ab\"cd\"ef\"\"\n");
   assert(last_non_quote_character("ab\"cd\"ef\"\"") == 'f');
   printf("testing: lots of them\"\"\"\"\"\"\"\"\"\"\"\"\"\"\n");
   assert(last_non_quote_character("lots of them\"\"\"\"\"\"\"\"\"\"\"\"\"\"") == 'm');
   printf("testing: !\n");
   assert(last_non_quote_character("!") == '!');
   printf("testing: \n");
   assert(last_non_quote_character("") == '\0');
   printf("testing: \"\n");
   assert(last_non_quote_character("\"") == '\0');
   printf("testing: \"\"\"\"\"\"\"\"\"\"\"\n");
   assert(last_non_quote_character("\"\"\"\"\"\"\"\"\"\"\"") == '\0');
   
   printf("\nSuccessful end of tests.\n\n\n");
   
   return EXIT_SUCCESS;
}
