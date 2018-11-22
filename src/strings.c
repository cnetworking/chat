#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "chat.h"

const int INPUT_SIZE = 128 + 1;
const int USERNAME_SIZE = 16 + 1;
const int MESSAGE_SIZE = USERNAME_SIZE + 2 + INPUT_SIZE;

char *concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void remove_newline(char *s) {
    for (int i = 0; i < sizeof(s); i++) {
        if (s[i] == '\n') {
            s[i] = '\0';
        }
    }
}

char *input(char *prompt) {
    char *buffer;
    size_t bufsize = 32;
    size_t characters;
    buffer = (char *)malloc(bufsize *sizeof(char));
    printf("%s", prompt);
    characters = getline(&buffer, &bufsize, stdin);
    return buffer;
}