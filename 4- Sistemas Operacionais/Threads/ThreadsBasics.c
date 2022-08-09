#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* routine_thread(void* args) {
    printf("Routine thread start\n");
    sleep(20);
    printf("Routine thread end\n");
    return NULL;
}

int main(int argc, char* argv[]) {

    pthread_t t1, t2;

    /*  
        pthread_create and pthread_join return 0
        if the callings have finished successfully
    */
    
    pthread_create(&t1, NULL, &routine_thread, NULL);
    pthread_create(&t2, NULL, &routine_thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}