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

struct socket_struct {
    int socket;
};

// The array that will hold all of the messages
char messages[256][256];
int message_count = 0;

void *read_thread(void *args) {
    // Get the contents from the argument (which is type 'struct socket_struct')
    struct socket_struct *client_socket_struct = args;
    int socket = client_socket_struct->socket;
    // Recieve loop
    while (1) {
        // Recieve the message (this is blocking)
        char server_response[MESSAGE_SIZE];
        recv(socket, &server_response, sizeof(server_response), 0);
        printf("client %d: %s", socket, server_response);
    }
    exit(0);
    
}

int main() {
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

    // Create array of client sockets
    int client_count = 0;
    struct socket_struct *client_sockets[MAX_CLIENTS];

    // Start listening to connections
    printf("awaiting connections\n");
    listen(server_socket, MAX_CLIENTS);

    // ---------- SETUP COMPLETE ----------

    // Accept connections from client sockets
    // while (client_count < 5) {
    while (1) {
        // Accept the connection
        struct socket_struct *client_socket_struct = malloc(sizeof(struct socket_struct *));
        client_socket_struct->socket = accept(server_socket, NULL, NULL);

        if (client_socket_struct->socket == -1) {
            printf("unable to accept client\n");
        } else {
            client_count++;
            pthread_t id;
            pthread_create(&id, NULL, read_thread, client_socket_struct);
        }
    }
    
    // Close the socket
    close(server_socket);
}