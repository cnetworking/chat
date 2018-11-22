#include <stdio.h>
#include "vector.h"
#include "../chat.h"

int main() {
	// declare and initialize a new vector
	Vector vector;
	vector_init(&vector);
    
    struct socket_struct *ss0 = malloc(sizeof(struct socket_struct *));
    ss0->socket = 10;
    struct socket_struct *ss1 = malloc(sizeof(struct socket_struct *));
    ss1->socket = 20;

	// fill it up with 150 arbitrary values
	// this should expand capacity up to 200
    vector_append(&vector, ss0);
    vector_append(&vector, ss1);

	// print out an arbitrary value in the vector
	for (int i = 0; i < 20; i++) {
		printf("%i\n", vector_get(&vector, i));	
	}

	// we're all done playing with our vector, 
	// so free its underlying data array
	vector_free(&vector);
}