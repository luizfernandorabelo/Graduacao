#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int fuel_tank = 0;
pthread_mutex_t tank_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t tank_cond = PTHREAD_COND_INITIALIZER;

void* attendant_turn(void* args) {
    while (1) {
        pthread_mutex_lock(&tank_mutex);
        fuel_tank += 15;
        printf("ATTENDANT: Just added 15l. Fuel amount = %dl\n", fuel_tank);
        pthread_mutex_unlock(&tank_mutex);
        pthread_cond_signal(&tank_cond);
        sleep(1);
    }
    return NULL;
}

void* car_turn(void* args) {
    while (1) {
        pthread_mutex_lock(&tank_mutex);
        while (fuel_tank < 40) {
            printf("CAR: Out of enough fuel! Waiting...\n");
            pthread_cond_wait(&tank_cond, &tank_mutex);
        }
        fuel_tank -= 40;
        printf("CAR: Consumed 40l. Fuel amount = %dl\n", fuel_tank);
        pthread_mutex_unlock(&tank_mutex);
    }
    return NULL;
}

int main(int argc, char* argv[]) {

    pthread_t car_thread, attendant_thread;

    pthread_mutex_init(&tank_mutex, NULL);
    pthread_cond_init(&tank_cond, NULL);

    /*
        - pthread_cond_wait:
            1. initialize the condition and unlock the mutex
            2. while the condition does not receive any signal:
                wait for the signal
            3. when the signal is received, lock the mutex back
        
        - pthread_cond_signal:
            1. sends a signal through the condition variable
        
        NOTE: sending a signal means that the variable tested in
              the thread while loop MAY have changed, but it is not
              guaranteed
    */

    if (pthread_create(&car_thread, NULL, &car_turn, NULL)) {
        fprintf(stderr, "Error creating car thread!\n");
    }
    if (pthread_create(&attendant_thread, NULL, &attendant_turn, NULL)) {
        fprintf(stderr, "Error creating attendant thread!\n");
    }

    if (pthread_join(car_thread, NULL)) {
        fprintf(stderr, "Error joining car thread!\n");
    }
    if (pthread_join(attendant_thread, NULL)) {
        fprintf(stderr, "Error joining attendant thread!\n");
    }

    pthread_mutex_destroy(&tank_mutex);
    pthread_cond_destroy(&tank_cond);

    return 0;
}