#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int sjedala[100] = {0};

void dohvacanje(){
    sleep(rand() % 3 + 1);
}

void *prijava(){
    sleep(rand() % 5 + 1);
    dohvacanje();

    int izbor_sjedala, potvrda_korisnika;
    while(1){
        izbor_sjedala = rand() % 100;
        potvrda_korisnika = rand() % 2;
        if(sjedala[izbor_sjedala] == 0 && potvrda_korisnika == 1){
            sleep(rand() % 2 + 1);
            sjedala[izbor_sjedala] = 1;
            break;
        }
    }
    return 0;
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    int i, zauzeta_sjedala = 0, slobodna_sjedala = 0;

    pthread_t *korisnici = calloc(100, sizeof(*korisnici));

    for(i = 0; i < 100; i++){
        pthread_create(&korisnici[i], NULL, prijava, NULL);
    }
    for(i = 0; i < 100; i++){
        pthread_join(korisnici[i], NULL);
    }

    for(i = 0; i < 100; i++){
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