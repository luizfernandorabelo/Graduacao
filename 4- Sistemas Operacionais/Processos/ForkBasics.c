#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    /*
        fork() returns:
            - zero: if the process is the own process created (child process)
            - positive value: if it is the parent process (value represents the process id of the child process)
            - negative value: if an error occurred
    */

    int fork_id = fork();

    printf("Fork id = %d\n", fork_id);
    printf("Current ID = %d\tParent ID = %d\n", getpid(), getppid());

    sleep(5);

    return 0;
}