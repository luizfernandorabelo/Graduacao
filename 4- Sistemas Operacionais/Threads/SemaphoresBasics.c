#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semaphore;


void* thread_routine(void* args) {
    sem_wait(&semaphore);
    sleep(1);
    printf("I'm here with thread %d\n", *(int*) args);
    sem_post(&semaphore);
    free(args);
}


int main(void) {

    pthread_t threads[THREAD_NUM];

    /*
        - The semaphore below is initialized with 0 processes and initial counter value of 2
        - sem_wait() decrements the counter value if it is greater than 0; otherwise it waits the counter value to be gt 0
        - sem_post() increments the counter value
    */

    sem_init(&semaphore, 0, 2); 

    for (int i = 0; i < THREAD_NUM; i++) {
        int* parameter = malloc(sizeof(int));
        *parameter = i;
        if (pthread_create(&threads[i], NULL, &thread_routine, parameter))
            fprintf(stderr, "Error to create thread %d\n", i);
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(threads[i], NULL))
            fprintf(stderr, "Error to join thread %d\n", i);
    }

    sem_destroy(&semaphore);

    return 0;
}