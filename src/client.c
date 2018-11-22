#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "chat.h"
#define IP "192.168.1.245"
#define PORT 3000

int main() {
    // Raw sockets are independent of an actual protocol - might be useful later
    // This program uses TCP
    
    // Main loop bool
    int loop = 0;

    // Create a socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    // server_address.sin_addr.s_addr = inet_addr(IP);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Make the connection to another socket
    int connection_status = connect(
      client_socket,
      (struct sockaddr *) &server_address,
      sizeof(server_address)
    );
    
    if (connection_status == -1) {
        printf("unable to create connection to server\n");
        printf("error code: %i\n", connection_status);
        exit(-1);
    } else {
        printf("connected to the server socket\n");
        loop = 1;
    }

    // Ask the user for a username
    // char *r_username = malloc(16);
    // printf("enter your name: ");
    // fgets(r_username, 16, stdin);
    // remove_newline(r_username);
    // char *username = malloc(USERNAME_SIZE + 2);
    // username = concat(r_username, ": ");

    // Main loop
    while (loop) {
        // Ask user for input
        char *message = malloc(MESSAGE_SIZE);
        printf("> ");
        fgets(message, sizeof(message), stdin);
        // m_remove_newline(message);
        // printf("you hit enter! and typed '%s'!\n", message);
        // Send data to the server
        // char *to_send = malloc(MESSAGE_SIZE);
        // // to_send = concat(username, message);
        // to_send = concat("bob: ", "hi");
        // send(client_socket, to_send, sizeof(to_send), 0);
        send(client_socket, message, MESSAGE_SIZE, 0);

        // Recieve data from the server
        // char server_response[MESSAGE_SIZE];
        // recv(client_socket, &server_response, sizeof(server_response), 0);
        // printf("server: %s\n", server_response);

    }
    
    // Close the socket
    close(client_socket);

    return 0;
}
