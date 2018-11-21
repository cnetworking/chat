#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

#define PORT 3000

int main() {
    // Create a string for the data that we will send to the client(s)
    char message[256] = "hi, im the server";

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

    // Start listening to connections
    int max_clients = 5;
    printf("awaiting connections\n");
    listen(server_socket, max_clients);

    // Accept connections from client sockets
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // Send data to the client
    send(client_socket, message, sizeof(message), 0);

    // Close the socket
    close(server_socket);
}
