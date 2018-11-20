#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {
    // Raw sockets are independent of an actual protocol
    // Create a socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3000);
    server_address.sin_addr.s_addr = INADDR_ANY; // Connecting to localhost

    // Make the connection to another socket
    struct sockaddr *ready_address = &server_address;
    int connection_status = connect(client_socket, ready_address, sizeof(server_address));
    
    if (connection_status == -1) {
        printf("unable to create connection to server\n");
    }

    // Recieve data from the server
    char server_response[256];
    recv(client_socket, &server_response, sizeof(server_response), 0);

    printf("server: %s\n", server_response);

    // Close the socket
    close(client_socket);

    return 0;
}