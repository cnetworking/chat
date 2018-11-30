#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

#include "chat.h"
#include "io/io.h"

int main(int argc, char **argv) {
    // Set the server's port number based off of arguments
    int port;
    if (argc < 2 || argc > 2 || to_int(argv[1]) <= 0) {
        // printf("syntax: ./server.out <port>\n");
        exit(-1);
    } else {
        port = to_int(argv[1]);
    }

    // Just some code to print this pretty little box
    char *ipv4 = get_ip("en0");
    int ipv4_size = strlen(ipv4);
    int ip_spaces = 18 - ipv4_size;
    
    int port_size = int_len(port);
    int p_spaces = abs(18 - port_size);

    clear();
    // printf("# # # # # # # # # # # # # # # # # # # #\n");
    // printf("#           SERVER INITIATED          #\n");
    // printf("#           PORT   %i", port);
    for (int i = 0; i < p_spaces; i++) {
        // printf(" ");
    }
    // printf(" #\n");
    // printf("#           IPv4   %s", ipv4);
    for (int i = 0; i < ip_spaces; i++) {
        // printf(" ");
    }
    // printf(" #\n");
    // printf("# # # # # # # # # # # # # # # # # # # #\n");

    // The array that will hold all of the messages
    List *messages = List_create();

    // Create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = INADDR_ANY;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the network
    bind(
      server_socket,
      (struct sockaddr *) &server_address,
      sizeof(server_address)
    );

    int client_count = 0;

    // Start listening to connections
    // printf("awaiting connections\n");
    listen(server_socket, MAX_CLIENTS);

    // ---------- SOCKET SETUP COMPLETE ----------
    
    // The array that stores all of the client sockets
    int *client_sockets = malloc(sizeof(int) * MAX_CLIENTS);

    // Start the writing thread (only need one of these)
    // Prepare the write thread arguments
    ServerWriteThreadArgs *args = malloc(sizeof(ServerWriteThreadArgs *));
    args->client_sockets = malloc(sizeof(int) * MAX_CLIENTS);
    args->client_sockets = client_sockets;
    args->messages = messages;
    
    // Start the thread itself
    pthread_t write_id;
    pthread_create(&write_id, NULL, server_write_thread, args);

    // Accept connections from client sockets
    while (client_count < 5) {
        // Accept the connection
        int accepted_socket = accept(server_socket, NULL, NULL);

        if (accepted_socket == -1) {
            // printf("unable to accept client\n");
        } else {
            // Add the socket to the list of sockets
            client_sockets[client_count] = accepted_socket;
            client_count++;

            // Prepare the read thread arguments
            ServerReadThreadArgs *args = malloc(sizeof(ServerReadThreadArgs *));
            args->messages = messages;
            args->socket = accepted_socket;
            
            pthread_t id;
            pthread_create(&id, NULL, server_read_thread, args);
        }
    }
    
    // Close the socket
    close(server_socket);

    // Free the list
    List_destroy(messages);
}