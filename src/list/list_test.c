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
    List_append(l, "bean");
    List_append(l, "junior");

    List_insert(l, 3, "HAROLD");
    List_insert(l, List_length(l), "CARL");
    List_insert(l, 0, "MIKE");

    List_remove(l, 2);

    List_print(l);
    printf("Length: %i\n", List_length(l));
    printf("Pop 3: %s\n", List_pop(l, 3));
    printf("Get 3: %s\n", List_get(l, 3));
    printf("Find \"junior\": %i\n", List_find(l, "junior"));

    List_destroy(l);

    return 0;
}