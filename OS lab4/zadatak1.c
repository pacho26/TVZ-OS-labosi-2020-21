#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int zbroj = 0;

int main(int argc, char *argv[]){
    setbuf(stdout, NULL); //sprječava da ljuska koristi međuspremnik
    if(argc < 2 || argc > 2){
        printf("Krivi broj argumenata!\n");
        exit(EXIT_FAILURE);
    }

    int br_procesa = atoi(argv[1]), i;
    pid_t pid_djeteta;

    for(i = 0; i < br_procesa;i++){
        switch(pid_djeteta = fork()) {
            case -1:
                printf("Nastao je problem sa naredbom fork()\n");
                exit(EXIT_FAILURE);
            case 0:
                zbroj++;
                exit(EXIT_SUCCESS);
            default:
                wait(NULL);
        }
    }

    printf("Zbroj: %d\n", zbroj);

    exit(EXIT_SUCCESS);
}