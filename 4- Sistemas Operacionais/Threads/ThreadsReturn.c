#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void* roll_dice(void* args) {
    int* value = malloc(sizeof(int));
    *value = rand() % 6 + 1;
    return value;
}

int main(int argc, char* argv[]) {

    srand(time(NULL));

    pthread_t rd_thread;

    if (pthread_create(&rd_thread, NULL, &roll_dice, NULL)) {
        fprintf(stderr, "An error occurred at thread creation!\n");
        exit(1);
    }

    int* rd_return = 0;
    if (pthread_join(rd_thread, (void**) &rd_return)) {
        fprintf(stderr, "An error occurred at thread joining!\n");
        exit(2);
    }

    printf("Dice = %d\n", *rd_return);

    free(rd_return);

    return 0;
}