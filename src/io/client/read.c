#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "client.h"
#include "../../chat.h"

void *client_read_thread(void *argsp) {
    // Parse the argument
    ClientReadThreadArgs *args = argsp;
    char *last_msg = *args->last_msg;
    int *client_socket = args->socket;

    // Recieve data from the server
    while (1) {
        char server_response[256];
        recv(*client_socket, &server_response, sizeof(server_response), 0);
        if (strcmp(server_response, last_msg) != 0) {
            // printf("server response: %s-----------last message: %s-----", server_response, last_msg);
            // printf("server: %s\n", server_response);
        }
    }
    return NULL;
}