#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"

int main() {
    List *l = List_create();

    List_append(l, "jim");
    List_append(l, "bob");
    List_append(l, "joe");
    

    List_insert(l, 3, "HAROLD");
    List_insert(l, List_length(l), "CARL");
    List_insert(l, 0, "MIKE");

    char *a = List_pop(l, List_length(l) - 1);
    printf("%s\n", a);

    List_print(l);
    
    List_destroy(l);

    return 0;
}