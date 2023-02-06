#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char* sub_string(char* str, int pos) {
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

int main() {
    char str[] = "hello world...";
    printf("string: %s\n", str);
    printf("substr: %s\n", sub_string(str, 6));

    return 0;
}