#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

    int process_id = fork();
    int n;

    if (process_id == 0) {  // if it is the child process
        n = 10;
        printf("The child process will print the numbers from 1 to 10\n");
    }
    else {  // if it is the main process
        n = 20;
        printf("The parent process will print the numbers from 11 to 20\n");
    }

    /*
        In this case, wait is used to make sure that the child process
        is completed before the main process continues its execution.
        Otherwise, the OS will execute them in a non-deterministic order.
        The wait() function returns the process id of the child process
        that it will wait for.
    */

    if (process_id != 0) {  // if it is the main process
        wait(NULL); // wait to the child process to finish
    }

    for (int i = n - 9; i <= n; i++) {
        printf("%2d ", i);
        fflush(stdout);
    }

    printf("\n");

    return 0;
}