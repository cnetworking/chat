#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

#define PORT 3000
#define MAX_CLIENTS 5

char *concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
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

    // Setup recieve timeout
    struct timeval read_timeout;
    read_timeout.tv_sec = 0;
    read_timeout.tv_usec = 10;
    setsockopt(server_socket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof(read_timeout));

    // Bind the socket to the network
    bind(
      server_socket,
      (struct sockaddr *) &server_address,
      sizeof(server_address)
    );

    // Create array of client sockets
    int client_count = 0;
    int client_sockets[MAX_CLIENTS];

    // Start listening to connections
    printf("awaiting connections\n");
    listen(server_socket, MAX_CLIENTS);

    // Main server loop
    while (1) {
        int c = 0;
        // Accept connections from client sockets
        while (client_count < 5) {
            printf("im in here: %i\n", c);
            c++;
            // Accept the connection
            int client_socket;
            printf("before accept\n");
            client_socket = accept(server_socket, NULL, NULL);
            printf("after accept\n");
            if (client_socket == -1) {
                printf("unable to accept client\n");
            } else {
                // Add this connection to the array of connections
                client_sockets[client_count] = client_socket;
                client_count++;
                break;
            }
        }
        
        // Recieve messages from clients
        for (int i = 0; i < client_count; i++) {
            char server_response[256];
            recv(client_sockets[i], &server_response, sizeof(server_response), 0);
            printf("client: %s\n", server_response);
            char *message = concat("broadcast: ", server_response);
            for (int i = 0; i < client_count; i++) {
                send(client_sockets[i], message, sizeof(message), 0);
            }
        }

        // Create a string for the data that we will send to the client(s)
        char message[256] = "hi all!";
        // Send data to the clients
        for (int i = 0; i < client_count; i++) {
            send(client_sockets[i], message, sizeof(message), 0);
        }
    }

    // Close the socket
    close(server_socket);
}
