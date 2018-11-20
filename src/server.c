#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

#define PORT 3000
#define MAX_CLIENTS 5

int main() {
    // Create a string for the data that we will send to the client(s)
    char message[256] = "hi all!";

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
    int client_sockets[MAX_CLIENTS];

    // Start listening to connections
    printf("awaiting connections\n");
    listen(server_socket, MAX_CLIENTS);

    // Accept connections from client sockets
    while (client_count < 5) {
        int client_socket;
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1) {
            printf("unable to accept client\n");
        } else {
            client_sockets[client_count] = client_socket;
            client_count++;
            // break;
        }
        

        char server_response[256];
        recv(client_socket, &server_response, sizeof(server_response), 0);
        printf("client: %s\n", server_response);

    }

    // Send data to the clients
    for (int i = 0; i < MAX_CLIENTS; i++) {
        send(client_sockets[i], message, sizeof(message), 0);
    }

    // Close the socket
    // close(server_socket);
}
