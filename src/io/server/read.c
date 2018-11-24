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
        printf("im the server and im reading\n");
        // Recieve the message (recv() is blocking)
        char server_response[MSG_SIZE];
        char *buffer = "";
        recv(socket, &server_response, sizeof(server_response), 0);
        printf("buffer: %s", buffer);
        
        // Add the message to the list of messages
        remove_newline(server_response);
        char *msg = concat(buffer, server_response);
        List_insert(messages, List_length(messages), msg);
    }
    exit(0);
}