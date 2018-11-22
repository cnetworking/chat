#ifndef LIST_H
#define LIST_H

#define MAX_STR_LEN 80

typedef struct link_node {
	char node_str[MAX_STR_LEN];
	struct link_node *next;
} node;

int compare_node(struct link_node *n1, struct link_node *n2);
struct link_node *add_node(struct link_node	*list, struct link_node *node);
void display_list(struct link_node *head);
void free_list(node *head);
void cleanInput(char* input);

#endif