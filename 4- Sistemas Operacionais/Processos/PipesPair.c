#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char* argv[]) {

    srand(time(NULL));

    int fds_c2p[2] = {0};   // file descriptors for the child to parent communication
    int fds_p2c[2] = {0};   // file descriptors for the parent to child communication

    if (pipe(fds_c2p) == -1 || pipe(fds_p2c) == -1) {
        fprintf(stderr, "An error occurred when opening the pipes!\n");
        exit(1);
    }

    int fork_id = fork();

    /*
        The goal of the algorithm is to send some number to the child
        process and receive the result of its multiplication by 4.
        When there is no information to be read in certain file descriptor,
        the process will automatically wait for the information to be written.
    */

    if (fork_id == 0) { // if it is the child process
        close(fds_c2p[READ_END]);
        close(fds_p2c[WRITE_END]);
        int numberReceived = 0;
        read(fds_p2c[READ_END], &numberReceived, sizeof(int));
        printf("Child received %d from the parent\n", numberReceived);
        int numberSent = 4 * numberReceived;
        write(fds_c2p[WRITE_END], &numberSent, sizeof(int));
        printf("Child sent %d to the parent\n", numberSent);
        close(fds_p2c[READ_END]);
        close(fds_c2p[WRITE_END]);
    }
    else {  // if it is the parent process
        close(fds_p2c[READ_END]);
        close(fds_c2p[WRITE_END]);
        int numberSent = rand() % 10;
        write(fds_p2c[WRITE_END], &numberSent, sizeof(int));
        printf("Parent sent %d to the child\n", numberSent);
        int numberReceived = 0;
        read(fds_c2p[READ_END], &numberReceived, sizeof(int));
        printf("Parent received %d from the child\n", numberReceived);
        close(fds_c2p[READ_END]);
        close(fds_p2c[WRITE_END]);
        wait(NULL);
    }

    return 0;
}