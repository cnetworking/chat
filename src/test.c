#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "chat.h"
#include "vector/vector.h"

int main() {


    List *myList = List_create();

    // declare and initialize a new vector
    Vector *myVector;
    vector_init(myVector);

    for (int i = 0; i < 20; i++) {
        vector_append(myVector, i);
    }



    for (int i = 0; i < 20; i++) {
        printf("%i\n", vector_get(myVector, i));
    }

    // we're all done playing with our vector, 
    // so free its underlying data array




    // struct server_write_thread_args *args = malloc(sizeof(struct server_write_thread_args *));
    // // args->messages = messages;
    // args->client_sockets = client_sockets;
    
    vector_free(myVector);
    return 0;
}