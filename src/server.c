#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {
    // Create a string for the data that we will send to the client(s)
    char message[256] = "hi all!";

    // Create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the network
    struct sockaddr *ready_address = &server_address;
    bind(server_socket, ready_address, sizeof(server_address));

    // Start listening to connections
    int max_clients = 5;
    listen(server_socket, max_clients);

    // Accept connections from client sockets
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // Send data to the client
    send(client_socket, message, sizeof(message), 0);

    // Close the socket
    close(server_socket);
}