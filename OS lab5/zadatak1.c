#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define BROJ_SJEDALA 100

int sjedala[BROJ_SJEDALA] = {0};
pthread_mutex_t mutex[BROJ_SJEDALA];

void dohvacanje(){
    sleep(rand() % 3 + 1);
}

void *prijava(){
    sleep(rand() % 5 + 1);
    dohvacanje();

    int izbor_sjedala, potvrda_korisnika;
    while(1){
        izbor_sjedala = rand() % BROJ_SJEDALA;
        potvrda_korisnika = rand() % 2;
        pthread_mutex_lock(&mutex[izbor_sjedala]);
        if(sjedala[izbor_sjedala] == 0 && potvrda_korisnika == 1){
            sleep(rand() % 2 + 1);
            sjedala[izbor_sjedala] = 1;
            pthread_mutex_unlock(&mutex[izbor_sjedala]);
            break;
        }
        pthread_mutex_unlock(&mutex[izbor_sjedala]);
    }
    return 0;
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    int i, zauzeta_sjedala = 0, slobodna_sjedala = 0;

    for(i = 0; i < BROJ_SJEDALA; i++){
        pthread_mutex_init(&mutex[i], NULL);
    }
    pthread_t *korisnici = calloc(BROJ_SJEDALA, sizeof(*korisnici));

    for(i = 0; i < BROJ_SJEDALA; i++){
        pthread_create(&korisnici[i], NULL, prijava, NULL);
    }
    for(i = 0; i < BROJ_SJEDALA; i++){
        pthread_join(korisnici[i], NULL);
    }

    for(i = 0; i < BROJ_SJEDALA; i++){
        pthread_mutex_destroy(&mutex[i]);
    }

    for(i = 0; i < BROJ_SJEDALA; i++){
        if(sjedala[i] == 0){
            slobodna_sjedala++;
        }
        else{
            zauzeta_sjedala++;
        }
    }

    printf("Broj zauzetih sjedala: %d\n", zauzeta_sjedala);
    printf("Broj slobodnih sjedala: %d\n", slobodna_sjedala);

    return 0;
}