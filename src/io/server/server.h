#ifndef SERVER_H
#define SERVER_H

// The server's read thread
void *server_read_thread(void *argsp);

// The server's write thread
void *server_write_thread(void *argsp);

#endif