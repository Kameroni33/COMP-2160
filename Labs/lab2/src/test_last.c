#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// Write your last_non_quote_character function here

int main()
{
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
   
   printf("\nSuccessful end of tests.\n");
   
   return EXIT_SUCCESS;
}