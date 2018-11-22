#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "chat.h"
int main() {

    List *myList = List_create();
    List_append(myList, "1");
    List_append(myList, "2");
    List_append(myList, "3");
    List_append(myList, "4");
    List_print(myList);
    // // declare and initialize a new vector
    // Vector *vector;
    // vector_init(vector);

    // for (int i = 0; i < 20; i++) {
    //     vector_append(vector, i);
    // }

    // // print out an arbitrary value in the vector
    // for (int i = 0; i < 20; i++) {
    //     printf("%i\n", vector_get(vector, i));
    // }

    // // we're all done playing with our vector, 
    // // so free its underlying data array
    // vector_free(vector);
    // return 0;
}