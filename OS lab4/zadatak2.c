#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

int zbroj = 0;

void *zbrajanje(){
    zbroj++;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Krivi broj argumenata!\n");
        exit(EXIT_FAILURE);
    }

    int br_dretvi = atoi(argv[1]);
    pthread_t *dretva = calloc(br_dretvi, sizeof(*dretva));
    int i;

    for(int i = 0; i < br_dretvi; i++){
        pthread_create(&dretva[i], NULL, zbrajanje, NULL);
    }
    for(int i = 0; i < br_dretvi; i++){
        pthread_join(dretva[i], NULL);
    }

    printf("Zbroj: %d\n", zbroj);

    exit(EXIT_SUCCESS);
}

