#ifndef CHAT_H
#define CHAT_H

#include "list/list.h"

struct socket_struct {
    int socket;
};

struct server_read_thread_args {
    struct socket_struct *socket_struct;
    List *messages;
};

char *concat(const char *s1, const char *s2);
void remove_newline(char *s);
char *m_getline();
char *input(char *prompt);

#endif