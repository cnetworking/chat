#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input(char *prompt) {
    char *buffer;
    size_t bufsize = 32;
    size_t characters;
    buffer = (char *)malloc(bufsize *sizeof(char));
    printf("%s", prompt);
    characters = getline(&buffer, &bufsize, stdin);
    return buffer;
}

int main() {
    
    printf("%s", input("enter something: "));
    return(0);
}