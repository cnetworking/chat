#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <pthread.h>

#include "chat.h"
#include "io/io.h"

#define IP "192.168.1.8"
#define PORT 3000

int main() {
    printf("# # # # # # # # # # # # # # # # # # # #\n");
    printf("#           CLIENT INITIATED          #\n");
    printf("# # # # # # # # # # # # # # # # # # # #\n");
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
    char *raw_username = input("username: ");
    // remove_newline(raw_username);
    // char *username = raw_username;

    // char *username = concat(raw_username, ": ");
    // printf("%s\n", username);

    pthread_t id;
    pthread_create(&id, NULL, client_read_thread, &client_socket);

    // Main loop
    while (loop) {
        // Ask user for input
        char *message = input("> ");
        // remove_newline(message);
        // char *to_send = concat(username, message);
        // printf("to send: %s", to_send);
        
        // Send the data to the server
        // send(client_socket, to_send, sizeof(to_send), 0);
        send(client_socket, message, sizeof(message), 0);

        

    }
    
    // Close the socket
    close(client_socket);

    return 0;
}
