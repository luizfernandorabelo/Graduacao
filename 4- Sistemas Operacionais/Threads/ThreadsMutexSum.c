#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_routine(void* args) {
    for (int i = 0; i < 5000000; i++) {
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char* argv[]) {

    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);

    if (pthread_create(&t1, NULL, &thread_routine, NULL)) {
        fprintf(stderr, "Failed to create thread t1!\n");
    }
    if (pthread_create(&t2, NULL, &thread_routine, NULL)) {
        fprintf(stderr, "Failed to create thread t2!\n");
    }

    if (pthread_join(t1, NULL)) {
        fprintf(stderr, "Failed to join thread t1!\n");
    }
    if (pthread_join(t2, NULL)) {
        fprintf(stderr, "Failed to join thread t2!\n");
    }

    printf("Slower, but correct one million = %d\n", sum);

    pthread_mutex_destroy(&mutex);

    return 0;
}