#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int broj_jela;
pthread_mutex_t mutex;
bool tin_zavrsio, davor_zavrsio, ivica_zavrsio, ivan_zavrsio;
char* jelo_na_stolu = "prazan stol";
char* jela[8] = {"čokolada", "ćevapi", "janjetina", "štrukle", "grah", "keksi",  "kelj", "jabuka"};

typedef struct{
    int pojedeno_jelo;
    int odbijeno_jelo;
    int prazan_stol;
} Jelo_aktivnosti;

void *ispis(char* ime, Jelo_aktivnosti status){
    pthread_mutex_lock(&mutex);
    printf("\n---------------%s---------------\n", ime);
    printf("Pojedenih jela: %d\nOdbijenih jela: %d\nDočekao ga prazan stol: %d\n",
           status.pojedeno_jelo, status.odbijeno_jelo, status.prazan_stol);
    pthread_mutex_unlock(&mutex);
}

int ide_jesti(char* ime){
    pthread_mutex_lock(&mutex);
    int povratna_vrijednost;
    if(strcmp(jelo_na_stolu, "prazan stol") == 0){
        povratna_vrijednost = -1;
    }

    else{
        if (strcmp(ime, "Tin") == 0) {  //--------------------TIN--------------------
            if (jelo_na_stolu != jela[1] && jelo_na_stolu != jela[2]) {
                povratna_vrijednost = 1;
            }
            else{
                povratna_vrijednost = 0;
            }
        }

        else if (strcmp(ime, "Davor") == 0) {   //--------------------DAVOR--------------------
            if (jelo_na_stolu != jela[0] && jelo_na_stolu != jela[5]) {
                povratna_vrijednost = 1;
            }
            else{
                povratna_vrijednost = 0;
            }
        }

        else if (strcmp(ime, "Ivica") == 0) {   //--------------------IVICA--------------------
            if (jelo_na_stolu != jela[4] && jelo_na_stolu != jela[6]) {
                povratna_vrijednost = 1;
            }
            else{
                povratna_vrijednost = 0;
            }
        }

        else if (strcmp(ime, "Ivan") == 0) {   //--------------------IVAN--------------------
            if (jelo_na_stolu != jela[3]) {
                povratna_vrijednost = 1;
            }
            else{
                povratna_vrijednost = 0;
            }
        }

        if(povratna_vrijednost == 1){
            jelo_na_stolu = "prazan stol";
            broj_jela--;
            printf("%s jede.\n", ime);
            sleep(rand() % 3 + 2);

        }
    }
    pthread_mutex_unlock(&mutex);
    return povratna_vrijednost;
}

void programiranje(char *ime){
    printf("%s programira.\n", ime);
    int random_broj = rand() % 10 + 1, rezultat = 1;
    for(int i = 0; i < random_broj; i++){
        rezultat *= i;
    }
}

void spavanje(char *ime){
    printf("%s spava.\n", ime);
    sleep(rand() % 6 + 5);
}

void problemi_s_alfom(){
    printf("Tin je na servisu s Alfom.\n");
    int random_broj = rand() % 100 + 1;
    if(random_broj < 25){
        sleep(4);
    }
    else if(random_broj < 45){
        sleep(2);
    }
    else{
        sleep(rand() % 4 + 1);
    }
}

void *tin(){
    char* ime = "Tin";
    Jelo_aktivnosti status = {};
    while (broj_jela > 0) {
        spavanje(ime);
        sleep(2);   //uzeto u obzir da Tin dulje spava
        programiranje(ime);
        switch(ide_jesti(ime)) {
            case 1:
                status.pojedeno_jelo++;
                break;
            case 0:
                status.odbijeno_jelo++;
                break;
            default:
                status.prazan_stol++;
        }
        problemi_s_alfom();
    }
    tin_zavrsio = true;
    while(1){
        if(tin_zavrsio && davor_zavrsio && ivica_zavrsio && ivan_zavrsio){
            ispis(ime, status);
            break;
        }
    }
}

void *davor(){
    char* ime = "Davor";
    Jelo_aktivnosti status = {};
    while (broj_jela > 0) {
        spavanje(ime);
        programiranje(ime);
        switch(ide_jesti(ime)) {
            case 1:
                status.pojedeno_jelo++;
                break;
            case 0:
                status.odbijeno_jelo++;
                break;
            default:
                status.prazan_stol++;
        }
        printf("Davor gleda TV.\n");
        sleep(rand() % 3 + 2);
    }
    davor_zavrsio = true;
    while(1){
        if(tin_zavrsio && davor_zavrsio && ivica_zavrsio && ivan_zavrsio){
            ispis(ime, status);
            break;
        }
    }
}

void *ivica(){
    char* ime = "Ivica";
    Jelo_aktivnosti status = {};
    while (broj_jela > 0) {
        spavanje(ime);
        printf("Ivica igra tenis.\n");
        sleep(rand() % 3 + 2);
        switch(ide_jesti(ime)) {
            case 1:
                status.pojedeno_jelo++;
                break;
            case 0:
                status.odbijeno_jelo++;
                break;
            default:
                status.prazan_stol++;
        }
        programiranje(ime);
    }
    ivica_zavrsio = true;
    while(1){
        if(tin_zavrsio && davor_zavrsio && ivica_zavrsio && ivan_zavrsio){
            ispis(ime, status);
            break;
        }
    }

}

void *ivan(){
    char* ime = "Ivan";
    Jelo_aktivnosti status = {};
    while (broj_jela > 0) {
        spavanje(ime);
        printf("Ivan sluša sviranje klavira.\n");
        sleep(rand() % 3 + 2);
        switch(ide_jesti(ime)) {
            case 1:
                status.pojedeno_jelo++;
                break;
            case 0:
                status.odbijeno_jelo++;
                break;
            default:
                status.prazan_stol++;
        }
        programiranje(ime);
    }
    ivan_zavrsio = true;
    while(1){
        if(tin_zavrsio && davor_zavrsio && ivica_zavrsio && ivan_zavrsio){
            ispis(ime, status);
            break;
        }
    }
}

void *kuharica(){
    while (broj_jela > 0) {
        sleep(rand() % 2 + 1);  //kuharica kuha
        if(strcmp(jelo_na_stolu, "prazan stol") == 0){
            pthread_mutex_lock(&mutex);
            jelo_na_stolu = jela[rand() % 8];
            //printf("Kuharica postavlja %s na stol.\n", jelo_na_stolu);
            pthread_mutex_unlock(&mutex);
        }
        sleep(rand() % 2 + 1);  //kuharica odmara
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Unesen je krivi broj argumenata!\n");
    }
    pthread_mutex_init(&mutex, NULL);
    broj_jela = atoi(argv[1]);
    srand(time(NULL));

    pthread_t dretve[5];
    pthread_create(&dretve[0], NULL, tin, NULL);
    pthread_create(&dretve[1], NULL, davor, NULL);
    pthread_create(&dretve[2], NULL, ivica, NULL);
    pthread_create(&dretve[3], NULL, ivan, NULL);
    pthread_create(&dretve[4], NULL, kuharica, NULL);

    pthread_join(dretve[0], NULL);
    pthread_join(dretve[1], NULL);
    pthread_join(dretve[2], NULL);
    pthread_join(dretve[3], NULL);
    pthread_join(dretve[4], NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}