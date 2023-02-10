//-----------------------------------------
// NAME: Kameron Ronald
// STUDENT NUMBER: 7880495
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Saulo dos Santos
// ASSIGNMENT: assignment 1, QUESTION: question 1
// 
// REMARKS: This program is a c implementation of Duplicates.java.
//-----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 15

//------------------------------------------------------
// test_count_duplicate_words
//
// PURPOSE: tell me what it does! 
// INPUT PARAMETERS:
// Describe those parameters which accept data values.
// OUTPUT PARAMETERS:
// Describe those parameters which return values.
// Include the value returned by the routine if not void.
// Some of these may be the same as the input
// parameters.
//------------------------------------------------------
char* sub_string(char* str, int pos) {
    int substr_len = strlen(str) - pos;
    if (substr_len < 0 || pos < 0) {
        printf("!!! pos: %d index out of bound for string: '%s' !!!\n", pos, str);
        return "";
    }
    char* substr = malloc(sizeof (char) * (substr_len + 1));
    for (int i = 0; i < substr_len; i++) {
        substr[i] = str[(i + pos)];
    }
    substr[substr_len] = '\0';
    return substr;
}


//------------------------------------------------------
// find_word
//
// PURPOSE: tell me what it does! 
// INPUT PARAMETERS:
// Describe those parameters which accept data values.
// OUTPUT PARAMETERS:
// Describe those parameters which return values.
// Include the value returned by the routine if not void.
// Some of these may be the same as the input
// parameters.
//------------------------------------------------------
int find_word(char str[], char word[]) {
    char check_word[MAX_WORD_LENGTH] = "";
    int check_pos = 0;
    unsigned int dont_check_word, found = 0;
    char check_char;

    dont_check_word = 0;
    while (check_pos < strlen(str) && !found) {
        check_char = str[check_pos];
        if (!isalpha(check_char)) {
            if ( (strcmp(word, check_word) == 0) && !dont_check_word) {
                found = 1;
            }
            dont_check_word = 0;
            strcpy(check_word, "");
        } else {
            if (strlen(check_word) >= strlen(word)) {
                dont_check_word = 1;
            } else {
                strncat(check_word, &check_char, 1);
            }
        }
        check_pos++;
    }

    if (!found && !dont_check_word && strlen(word) > 0) {
        found = (strcmp(word, check_word) == 0);
    }

    return found;
}


//------------------------------------------------------
// count_duplicate_words
//
// PURPOSE: tell me what it does! 
// INPUT PARAMETERS:
// Describe those parameters which accept data values.
// OUTPUT PARAMETERS:
// Describe those parameters which return values.
// Include the value returned by the routine if not void.
// Some of these may be the same as the input
// parameters.
//------------------------------------------------------
int count_duplicate_words(char str[]) {
    int count = 0;
    char word[MAX_WORD_LENGTH] = "";
    printf("%s", word);
    int pos;
    char current_char;
    char* sub_string_ptr;

    pos = 0;
    while (pos < strlen(str) && count >= 0) {
        current_char = str[pos];
        if (!isalpha(current_char)) {
            if (strlen(word) > 0) {
                sub_string_ptr = sub_string(str, pos);
                if (find_word(sub_string_ptr, word)) {
                    count++;
                }
                strcpy(word, "");
            }
        } else {
            if (strlen(word) >= MAX_WORD_LENGTH) {
                count = -1;
            } else {
                strncat(word, &current_char, 1);
            }
        }
        pos++;
    }

    free(sub_string_ptr);

    return count;
}


//-------------------------------------------------------------------------------------------------
// test_count_duplicate_words
//
// PURPOSE: tests that count_duplicate_words returns what we expect
// INPUT PARAMETERS:
//  - (int) "expected" number of duplicate words expected
//  - (char*) "str" string to test
//  - (int*) "tests_executed" pointer to int on heap holding number of tests executes so far
//  - (int*) "tests_faile" pointer to int on heap holding number of tests failed so far
//-------------------------------------------------------------------------------------------------
void test_count_duplicate_words(int expected, char* str, int* tests_executed, int* tests_failed) {
    int result = count_duplicate_words(str);

    if (result == expected) {
        printf("Passed: %d from '%s'\n", result, str);
    } else {
        printf("FAILED: %d instead of %d from '%s'\n", result, expected, str);
        *tests_failed++;
    }

    *tests_executed++;
}


int main() {
    int* tests_executed = malloc(sizeof(int));
    int* tests_failed = malloc(sizeof(int));

    printf("Testing typical cases\n");
    test_count_duplicate_words(0, "hello world", tests_executed, tests_failed);
    test_count_duplicate_words(0, "bye-bye", tests_executed, tests_failed);
    test_count_duplicate_words(1, "the quick brown foxes jumped over the lazy dogs", tests_executed, tests_failed);
    test_count_duplicate_words(0, "The quick brown foxes jumped over the lazy dogs", tests_executed, tests_failed);
    test_count_duplicate_words(2, "A palindrome: a man a plan a canal panama", tests_executed, tests_failed);
    test_count_duplicate_words(8, "I felt happy because I saw the others were happy and because I knew I should feel happy but I wasn’t really happy", tests_executed, tests_failed);
    test_count_duplicate_words(3, "One fish two fish\nred fish blue\nfish", tests_executed, tests_failed);
    test_count_duplicate_words(5, "doo be \t doo be \t doo be \t  doo", tests_executed, tests_failed);
    test_count_duplicate_words(8, "... -- -- -- ...\n... -- -- -- ...", tests_executed, tests_failed);
    test_count_duplicate_words(26, "a b c d e f g h i j k l m n o p q r s t u v w x y z a b c d e f g h i j k l m n o p q r s t u v w x y z", tests_executed, tests_failed);

    printf("\nTesting empty cases\n");
    test_count_duplicate_words(0, "", tests_executed, tests_failed);
    test_count_duplicate_words(0, " ", tests_executed, tests_failed);
    test_count_duplicate_words(0, "\t \t", tests_executed, tests_failed);
    test_count_duplicate_words(0, "   \n  \n  ", tests_executed, tests_failed);

    printf("\nTesting invalid cases\n");
    test_count_duplicate_words(-1, "the word antidisestablishmentarianism is very long but antidisestablishmentarianism is a political movement", tests_executed, tests_failed);
    test_count_duplicate_words(-1, "abcdefghijabcdef", tests_executed, tests_failed);
    test_count_duplicate_words(0, "abcdefghijabcde", tests_executed, tests_failed);

    printf("\nTesting edge cases\n");
    test_count_duplicate_words(1, "go Jets go", tests_executed, tests_failed);
    test_count_duplicate_words(2, "tomato tomato potato potato", tests_executed, tests_failed);
    test_count_duplicate_words(2, " tomato tomato potato potato ", tests_executed, tests_failed);
    test_count_duplicate_words(7, "buffalo buffalo buffalo buffalo buffalo buffalo buffalo buffalo", tests_executed, tests_failed);

    printf("\nThese tests will be opposite in the C version\n");
    test_count_duplicate_words(1, "In Java, the strings may contain \0 in the interior", tests_executed, tests_failed);
    test_count_duplicate_words(0, "In C, the strings cannot contain \0 in the interior", tests_executed, tests_failed);

    printf("\nTotal number of tests executed: %d\n", *tests_executed);
    printf("Number of tests passed:         %d\n", (*tests_executed - *tests_failed));
    printf("Number of tests failed:         %d\n", *tests_failed);

    // free allocate variables
    free(tests_executed);
    free(tests_failed);

    printf("\nEnd of Process.\n\n");
    return 0;
}