#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>

void *myThread(void *vargp) {
    // sleep(0.1);
    while (1) {
        printf("my very own thread\n");
        // return NULL;
    }
}

void *myThread2(void *vargp) {
    // sleep(0.1);
    while (1) {
        printf("2 thread\n");
        // return NULL;
    }
}

int main() {
    
    pthread_t thread_id2;
    printf("Before Thread\n");
    pthread_create(&thread_id2, NULL, myThread2, NULL);
    pthread_join(thread_id2, NULL);
    printf("After Thread\n");

    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThread, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");

    exit(0);
}