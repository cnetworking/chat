#ifndef CHAT_H
#define CHAT_H

#include "list/list.h"

#define MAX_CLIENTS 5

typedef struct server_read_thread_args {
    int socket;
    List *messages;
} ServerReadThreadArgs;

typedef struct server_write_thread_args {
    int *client_sockets;
    List *messages;
} ServerWriteThreadArgs;

char *concat(const char *s1, const char *s2);
void remove_newline(char *s);
char *m_getline();
char *input(char *prompt);

int to_int(char stringNumber[]);
char *get_ip(char *type);
void clear();
int int_len(int i);

#endif