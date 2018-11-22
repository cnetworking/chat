#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

#include "chat.h"

#define PORT 3000
#define MAX_CLIENTS 5

void *read_thread(void *argsp) {
    // Get the contents from the argument
    struct server_read_thread_args *args = argsp;
    struct socket_struct *client_socket_struct = args->socket_struct;
    int socket = client_socket_struct->socket;
    List *messages = args->messages;

    // Recieve loop
    while (1) {
        // Recieve the message (this is blocking)
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
    // Get the contents of the arguments
    struct server_write_thread_args *args = argsp;
    List *messages = args->messages;

    // Setup a queue of messages to be sent
    int sent_messages = 0;
    List *queue = List_create();

    while (1) {
        if (List_length(messages) > sent_messages) {
            for (int i = sent_messages; i < List_length(messages); i++) {
                List_insert(messages, List_length(messages),  List_get(messages, i));
            }
            sent_messages = List_length(messages);
        }

        // if (List_length(queue) > 0) {
        //     char *msg = List_pop(queue);
        //     for(int i = 0; i < clients.size(); i++) {
        //         clients.get(i).out.println(msg);
        //     }
        // }

        if (List_length(queue) > 0) {
            char *msg = List_pop(queue, List_length(queue));
            printf("message in queue: %s", msg);
        }
    }
}

int main() {
    printf("# # # # # # # # # # # # # # # # # # # #\n");
    printf("#           SERVER INITIATED          #\n");
    printf("# # # # # # # # # # # # # # # # # # # #\n");

    // The array that will hold all of the messages
    List *messages = List_create();
    List_append(messages, "DESPACITO");
    List_append(messages, "luis");
    List_append(messages, "fonsi");
    List_append(messages, "99");

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
    
    // Start the writing thread (only need one of these)
    struct server_write_thread_args *args = malloc(sizeof(struct server_write_thread_args *));
    args->messages = messages;
    pthread_t write_id;
    pthread_create(&id, NULL, write_thread, args);

    // Accept connections from client sockets
    while (client_count < 5) {
        // Accept the connection
        struct socket_struct *client_socket_struct = malloc(sizeof(struct socket_struct *));
        client_socket_struct->socket = accept(server_socket, NULL, NULL);
        
        struct server_read_thread_args *args = malloc(sizeof(struct server_read_thread_args *));
        args->socket_struct = client_socket_struct;
        args->messages = messages;

        if (client_socket_struct->socket == -1) {
            printf("unable to accept client\n");
        } else {
            client_count++;
            pthread_t id;
            pthread_create(&id, NULL, read_thread, args);
        }
    }
    
    // Close the socket
    close(server_socket);

    // Free the list
    List_destroy(messages);
}