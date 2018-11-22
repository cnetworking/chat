#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INITIAL_CAPACITY 256

// Define a vector type
typedef struct {
	int size;
	int capacity;
	struct socket_struct *socket;
} Vector;

void vector_init(Vector *vector);
void vector_append(Vector *vector, struct socket_struct *ss);

struct socket_struct *vector_get(Vector *vector, int index);

void vector_double_capacity_if_full(Vector *vector);
void vector_free(Vector *vector);

#endif