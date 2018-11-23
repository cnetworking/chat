#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "chat.h"

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
    size_t bufsize = 256;
    size_t characters;
    buffer = (char *)malloc(bufsize *sizeof(char));
    printf("%s", prompt);
    characters = getline(&buffer, &bufsize, stdin);
    return buffer;
}

int to_int(char stringNumber[]) {
    // 1.
    if (!stringNumber) {
        printf("Parameter error\n");
        return NULL;
    }
    char numberSign = stringNumber[0];
    int isPositive = 1;
    int number = 0;
    int i = 0;

    // 2.
    if (numberSign < '0') {
        if (numberSign == '-') {
            isPositive = 0;
            i++;
        } else {
            printf("Number sign error: '%c'\n", numberSign);
            return NULL;
        }
    }

    // 3.
    int stringLength = strlen(stringNumber);

    while (i < stringLength) {
        int digit = stringNumber[i++] - '0';
        if (digit < 0 || digit > 9) {
            printf("Invalid character '%c' on the position '%d'\n", stringNumber[i - 1],(i - 1));
            return NULL;
        }
        number *= 10;
        number += digit;
    }

    // 4.
    if (isPositive) {
        return number;
    } else {
        return -number;
    }
}