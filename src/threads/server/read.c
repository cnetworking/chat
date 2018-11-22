#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "server.h"
#include "../../chat.h"

void *read_thread(void *args) {
    // Get the contents from the argument (which is type 'struct socket_struct')
    struct socket_struct *client_socket_struct = args;
    int socket = client_socket_struct->socket;
    // Recieve loop
    while (1) {
        // Recieve the message (this is blocking)
        char server_response[256];
        recv(socket, &server_response, sizeof(server_response), 0);
        printf("%s", server_response);
    }
    exit(0);
}