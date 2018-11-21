#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>

struct mystruct {
    int inner_thing;
};

void *myThread(void *args) {
    sleep(0.1);
    struct mystruct *t = args;
    printf("THING: %d", t->inner_thing);
}

int main() {
    
    struct mystruct *args = malloc(sizeof(struct mystruct));
    args->inner_thing = 22;

    pthread_t thread_id2;
    printf("Before Thread\n");
    pthread_create(&thread_id2, NULL, myThread, args);
    pthread_join(thread_id2, NULL);
    printf("After Thread\n");


    exit(0);
}