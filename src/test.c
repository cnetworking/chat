#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <pthread.h>

#define MSG_SIZE 10000

int main() {
    
    
    
    
    
    
    
    
    
    
    
    
    // printf("enter a username: ");
    char username[16];
    fgets(username, sizeof(username), stdin);
    strtok(username, "\n");
    
    // Call the write thread
    // pthread_t id;
    // pthread_create(&id, NULL, client_read_thread, &client_socket);

    // Main loop
    while (1) {
        // printf("> ");
        // Ask user for input
        char message[MSG_SIZE];
        fgets(message, sizeof(message), stdin);
        remove_newline(message);

        // If string is not null
        if (strcmp(message, "\n") != 0) {
            remove_newline(message);
            char *r = malloc(sizeof(char) * (MSG_SIZE + 16 + 1));
            r = concat(concat(username, ": "), message);
            printf("server: %s-----\n", r);
            // send(client_socket, r, sizeof(r), 0);
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}