/*
COMP 2160 - Lab2
Kameron Ronald (7880495)
Feb. 08, 2023
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// Write your last_non_quote_character function here
char last_non_quote_character(char* quote) {
   // keep track of current position in string
   int pos = 0;
   char last_char = '\0';
   // iterate through string until the end (ie. cureent character is '\0')
   while(quote[pos] != '\0') {
      printf("%c\n", quote[pos]);
      // if we find a \" return the previous character (if \" is the first character we will return \0)
      if (quote[pos] == '"') {
         return last_char;
      }
      last_char = quote[pos];
      pos++;
   }
   return '\0';
}


int main()
{
   printf("testing: hello world\n");
   printf("result: %c\n", last_non_quote_character("hello world"));
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
   
   printf("\nSuccessful end of tests.\n");
   
   return EXIT_SUCCESS;
}