#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "server.h"
#include "../../chat.h"

void *server_read_thread(void *argsp) {
    // Parse the argument
    ServerReadThreadArgs *args = argsp;
    int socket = args->socket;
    List *messages = args->messages;

    // Recieve loop
    while (1) {
        // Prepare the buffer
        char server_response[MSG_SIZE];
        char *buffer = "";
        memset(server_response, 0, strlen(server_response));
        
        // Recieve the message (recv() is blocking)
        recv(socket, &server_response, sizeof(server_response), 0);
        printf("%s\n", server_response);
        
        // Add the message to the list of messages
        remove_newline(server_response);
        char *msg = concat(buffer, server_response);
        List_insert(messages, List_length(messages), msg);
    }
    exit(0);
}