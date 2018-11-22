#ifndef CHAT_H
#define CHAT_H

#include "list/list.h"

struct socket_struct {
    int socket;
};

char *concat(const char *s1, const char *s2);
void remove_newline(char *s);
char *m_getline();
char *input(char *prompt);

const int INPUT_SIZE;
const int USERNAME_SIZE;
const int MESSAGE_SIZE;

#endif