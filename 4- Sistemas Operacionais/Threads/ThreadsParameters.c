#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void* print_routine(void* args) {
    printf("%d ", (*(int *) args));
    return NULL;
}

int main(int argc, char* argv[]) {

    /*
        This program contains 10 threads. Each one prints
        a prime number from the prime array.
    */

    pthread_t threads[10];
    int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

    for (int i = 0; i < 10; i++) {
        if (pthread_create(&threads[i], NULL, print_routine, (void *) &primes[i])) {
            fprintf(stderr, "Failed to create thread number %d\n", i);
            exit(1);
        }
    }

    for (int i = 0; i < 10; i++) {
        if (pthread_join(threads[i], NULL)) {
            fprintf(stderr, "Failed to join thread number %d\n", i);
            exit(2);
        }
    }

    printf("\n");

    return 0;
}