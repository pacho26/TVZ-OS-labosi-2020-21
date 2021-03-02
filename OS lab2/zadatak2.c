#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    setbuf(stdout, NULL);

    pid_t PID_djeteta;

    int n = atoi(argv[1]);
    int i;

    for(i = 1; i <= n; i++) {
        switch (PID_djeteta = fork()) {
            case -1:
                printf("Nastao je problem sa naredbom fork()\n");
                exit(EXIT_FAILURE);
            case 0:
                printf("Dijete #%d\n", i);
                exit(EXIT_SUCCESS);
            default:
                printf("Roditelj #%d\n", i);
                wait(NULL);
        }
    }
    exit(EXIT_SUCCESS);
}
