#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "server.h"
#include "../../chat.h"

void *server_write_thread(void *argsp) {
    printf("server write thread\n");

    // Get the contents of the arguments
    ServerWriteThreadArgs *args = argsp;
    List *messages = args->messages;
    int *client_sockets = args->client_sockets;

    // Setup a queue of messages to be sent
    int sent_messages = 0;
    List *queue = List_create();

    // Main loop to write new messages to all of the clients
    while (1) {
        if (List_length(messages) > sent_messages) {
            for (int i = sent_messages; i < List_length(messages); i++) {
                List_append(queue, List_get(messages, i));
            }
            sent_messages = List_length(messages);
        }

        if (List_length(queue) > 0) {
            char *msg = List_pop(queue, List_length(queue) - 1);
            printf("MSG: %s", msg);
            for(int i = 0; i < MAX_CLIENTS; i++) {
                send(client_sockets[i], msg, strlen(msg), 0);
            }
        }
    }
}