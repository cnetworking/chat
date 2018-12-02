#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "client.h"
#include "../../chat.h"

void *client_read_thread(void *argsp) {
    // Parse the argument
    int *client_socket = argsp;

    // Recieve data from the server
    while (1) {
        char server_response[MSG_SIZE];
        memset(server_response, 0, strlen(server_response));
        recv(*client_socket, &server_response, sizeof(server_response), 0);
        printf("%s\n", server_response);
    }
    return NULL;
}