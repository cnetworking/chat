#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

#include "chat.h"
#include "vector/vector.h"

#define PORT 3000

void *read_thread(void *argsp) {
    // Parse the argument
    ServerReadThreadArgs *args = argsp;
    int socket = args->socket;
    List *messages = args->messages;

    // Recieve loop
    while (1) {
        // Recieve the message (recv() is blocking)
        char server_response[100];
        char *buffer = "";
        recv(socket, &server_response, sizeof(server_response), 0);
        printf("%s", server_response);
        
        // Add the message to the list of messages
        remove_newline(server_response);
        char *msg = concat(buffer, server_response);
        List_insert(messages, List_length(messages), msg);
    }
    exit(0);
}

void *write_thread(void *argsp) {
    printf("i, the write thread, am running\n");

    // Get the contents of the arguments
    ServerWriteThreadArgs *args = argsp;
    List *messages = args->messages;
    int *client_sockets = args->client_sockets;

    // Setup a queue of messages to be sent
    int sent_messages = 0;
    List *queue = List_create();

    while (1) {
        printf("oh hi\n");
        if (List_length(messages) > sent_messages) {
            for (int i = sent_messages; i < List_length(messages); i++) {
                List_append(queue, List_get(messages, i));
            }
            sent_messages = List_length(messages);
        }

        if (List_length(queue) > 0) {
            List_pop(queue, List_length(queue));
            for(int i = 0; i < MAX_CLIENTS; i++) {
                printf("sending %s to %d\n", msg, client_sockets[i]);
                send(client_sockets[i], msg, sizeof(msg), 0);
            }
        }
    }
}

// void *write_thread(void *argsp) {
//     return NULL;
// }

int main() {
    printf("# # # # # # # # # # # # # # # # # # # #\n");
    printf("#           SERVER INITIATED          #\n");
    printf("# # # # # # # # # # # # # # # # # # # #\n");

    // The array that will hold all of the messages
    List *messages = List_create();
    // List_append(messages, "DESPACITO");
    // List_append(messages, "luis");
    // List_append(messages, "fonsi");
    // List_append(messages, "99");

    // Create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the network
    bind(
      server_socket,
      (struct sockaddr *) &server_address,
      sizeof(server_address)
    );

    int client_count = 0;

    // Start listening to connections
    printf("awaiting connections\n");
    listen(server_socket, MAX_CLIENTS);

    // ---------- SOCKET SETUP COMPLETE ----------
    
    // The array that stores all of the client sockets
    int *client_sockets = malloc(sizeof(int) * MAX_CLIENTS);

    // Start the writing thread (only need one of these)
    // Prepare the write thread arguments
    ServerWriteThreadArgs *args = malloc(sizeof(ServerWriteThreadArgs *));
    args->client_sockets = malloc(sizeof(int) * MAX_CLIENTS);
    args->client_sockets = client_sockets;
    args->messages = messages;
    
    // Start the thread itself
    pthread_t write_id;
    pthread_create(&write_id, NULL, write_thread, args);

    // Accept connections from client sockets
    while (client_count < 5) {
        // Accept the connection
        int accepted_socket = accept(server_socket, NULL, NULL);

        if (accepted_socket == -1) {
            printf("unable to accept client\n");
        } else {
            // Add the socket to the list of sockets
            client_sockets[client_count] = accepted_socket;
            client_count++;

            // Prepare the read thread arguments
            ServerReadThreadArgs *args = malloc(sizeof(ServerReadThreadArgs *));
            args->messages = messages;
            args->socket = accepted_socket;
            
            pthread_t id;
            pthread_create(&id, NULL, read_thread, args);
        }
    }
    
    // Close the socket
    close(server_socket);

    // Free the list
    List_destroy(messages);
}