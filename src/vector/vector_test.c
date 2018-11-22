#include <stdio.h>
#include "vector.h"

int main() {
	// declare and initialize a new vector
	Vector vector;
	vector_init(&vector);

	// fill it up with 150 arbitrary values
	// this should expand capacity up to 200
	for (int i = 0; i < 20; i++) {
		vector_append(&vector, i + 2);
	}

	// print out an arbitrary value in the vector
	for (int i = 0; i < 20) {
		printf("%i\n", vector_get(&vector, i));	
	}

	// we're all done playing with our vector, 
	// so free its underlying data array
	vector_free(&vector);
}