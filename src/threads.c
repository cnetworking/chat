#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>

void *myThread(void *args) {
    sleep(0.1);
    int *thing = args;
    printf("THING: %d", *thing);
}

int main() {
    
    int *ip = malloc(sizeof(int *));
    *ip = 20;

    pthread_t thread_id2;
    printf("Before Thread\n");
    pthread_create(&thread_id2, NULL, myThread, ip);
    pthread_join(thread_id2, NULL);
    printf("After Thread\n");


    exit(0);
}