#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

#define PORT 3000
#define MAX_CLIENTS 5

// Use to concat two strings
char *concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

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
    printf("this socket is %d\n", socket);
    
    // Recieve loop
    while (1) {
        // Recieve the message (this is blocking)
        char server_response[256];
        recv(socket, &server_response, sizeof(server_response), 0);
        printf("client %d: %s\n", socket, server_response);
    }
    
    // char server_response[256];
    // while (recv(socket, &server_response, sizeof(server_response), 0)>0) {
    //     printf("Message Received: %s\n", server_response);
    // }
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

    // // Setup recieve timeout and make recv non blocking. This makes accept block
    // struct timeval read_timeout;
    // read_timeout.tv_sec = 0;
    // read_timeout.tv_usec = 10;
    // setsockopt(server_socket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof(read_timeout));

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
        printf("main loop running\n");
        // Accept the connection
        struct socket_struct *client_socket_struct = malloc(sizeof(struct socket_struct *));
        
        printf("before accept\n");
        client_socket_struct->socket = accept(server_socket, NULL, NULL);
        printf("after accept\n");

        if (client_socket_struct->socket == -1) {
            printf("unable to accept client\n");
        } else {
            // client_sockets[client_count] = client_socket_struct;
            client_count++;
            pthread_t id;
            printf("Before Thread\n");
            pthread_create(&id, NULL, read_thread, client_socket_struct);
            // pthread_join(id, NULL);
            printf("After Thread\n");

        }
    }
    
    // // Recieve messages from clients
    // for (int i = 0; i < client_count; i++) {
    //     char server_response[256];
    //     recv(client_sockets[i], &server_response, sizeof(server_response), 0);
    //     printf("client: %s\n", server_response);
    //     char *message = concat("broadcast: ", server_response);
    //     for (int i = 0; i < client_count; i++) {
    //         send(client_sockets[i], message, sizeof(message), 0);
    //     }
    // }

    // // Create a string for the data that we will send to the client(s)
    // char message[256] = "hi all!";
    // // Send data to the clients
    // for (int i = 0; i < client_count; i++) {
    //     send(client_sockets[i], message, sizeof(message), 0);
    // }

    // Close the socket
    close(server_socket);
}
