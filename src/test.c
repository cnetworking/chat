#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "chat.h"

int main() {
    char *name = input("enter your name: ");
    remove_newline(name);
    char *color = input("enter your favorite color: ");
    remove_newline(color);
    char *food = input("enter your favorite food: ");
    remove_newline(food);

    printf("START%s %s %sEND", name, color, food);
    
    return(0);
}