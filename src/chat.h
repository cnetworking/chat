#ifndef CHAT_H
#define CHAT_H

char *concat(const char *s1, const char *s2);
char *m_getline();

const int INPUT_SIZE = 128 + 1;
const int USERNAME_SIZE = 16 + 1;
const int MESSAGE_SIZE = USERNAME_SIZE + 2 + INPUT_SIZE;

#endif