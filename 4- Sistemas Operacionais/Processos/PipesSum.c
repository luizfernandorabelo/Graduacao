#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char* argv[]) {

    /*
        The idea of the following algorithm is to create 2 different processes to
        sum the elements of single array. For that, two partial sums are evaluated
        and summed up (via pipe communication) to find the total sum
    */

    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int array_size = sizeof(array) / sizeof(int);
    int start_idx, end_idx, sum = 0;

    int fds[2] = {};

    if (pipe(fds) == -1) {
        fprintf(stderr, "An error occurred when opening the pipe!\n");
        exit(1);
    }

    int fork_id = fork();

    if (fork_id == 0) { // if it is the child process
        start_idx = 0;
        end_idx = array_size / 2;;
    }
    else {  // if it is the main process
        start_idx = array_size / 2 + 1;
        end_idx = array_size - 1;
    }

    for (int i = start_idx; i <= end_idx; i++) {
        sum += array[i];
    }

    printf("Partial sum = %d\n", sum);

    if (fork_id == 0) {
        close(fds[READ_END]);
        write(fds[WRITE_END], &sum, sizeof(int));
        close(fds[WRITE_END]);
    }
    else {
        wait(NULL);
        close(fds[WRITE_END]);
        int child_sum = 0;
        read(fds[READ_END], &child_sum, sizeof(int));
        close(fds[READ_END]);
        printf("The total sum is %d\n", sum + child_sum);
    }

    return 0;
}