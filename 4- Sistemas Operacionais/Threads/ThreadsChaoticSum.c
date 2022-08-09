#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum = 0;

void* thread_routine(void* args) {
    for (int i = 0; i < 500000; i++) {
        /*
            If the value of sum is changed in the middle of the execution
            of the following line, the final result becomes chaotic
        */
        sum++;  // 1st load; 2nd inc; 3rd store back
    }
    return NULL;
}

int main(int argc, char* argv[]) {

    pthread_t t1, t2;

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

    printf("One million = %d?\n", sum);

    return 0;
}