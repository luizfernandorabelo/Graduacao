#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char* argv[]) {

    /*
        the function kill will send a signal (some integer code)
        representing the event action to be performed. Some of the
        event actions are abort, kill, hang-up, interrupt...
    */

    int fork_id = fork();

    if (fork_id == 0) { // if it is the child process
        while (1) {
            printf("CHILD: I'm a rebel child process, nobody can stop me!\n");
            usleep(300000);
        }
    }
    else {  // if it is the parent process
        sleep(2);
        printf("PARENT: Actually, I can!\n");
        kill(fork_id, SIGKILL);
    }

    return 0;
}