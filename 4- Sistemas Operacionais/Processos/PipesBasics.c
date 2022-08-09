#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char* argv[]) {

    /*
        For creating a pipe, we need to pass an array which will
        store the file descriptors (access keys) to the read (fd[0])
        and write (fd[1]) ends of the pipe
    */

    int fds[2] = {0};

    if (pipe(fds) == -1) {
        fprintf(stderr, "An error occurred when opening the pipe!\n");
        exit(1);
    }

    int fork_id = fork();

    if (fork_id == 0) { // if it is the child process
        close(fds[READ_END]);
        int numberWritten;
        printf("Input a number: ");
        scanf("%d", &numberWritten);
        write(fds[WRITE_END], &numberWritten, sizeof(int));
        close(fds[WRITE_END]);
    }
    else {
        wait(NULL); // waits to the child process to finish
        close(fds[WRITE_END]);
        int numberRead;
        read(fds[READ_END], &numberRead, sizeof(int));
        close(fds[READ_END]);
        printf("Got %d from child process\n", numberRead);
    }
    
    return 0;
}