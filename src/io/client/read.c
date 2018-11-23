#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "client.h"
#include "../../chat.h"

void *client_read_thread(void *argsp) {
    // Parse the argument
    int *client_socket = argsp;

    // Recieve data from the server
    while (1) {
        char server_response[256];
        recv(*client_socket, &server_response, sizeof(server_response), 0);
        printf("server: %s\n", server_response);
    }
    return NULL;
}