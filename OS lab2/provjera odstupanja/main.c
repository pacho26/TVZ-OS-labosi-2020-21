#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char srodstvo[20+1];
    int redni_broj;
}Proces;

int main()
{
    int n = 0, i, broj_ponavljanja = 0;

    FILE *fin = fopen("vanjska300000.txt","r");
    Proces *niz = (Proces*)malloc(sizeof(Proces)*30000000);

    while(fscanf(fin, "%[^ ] #%d%*[\n]", niz[n].srodstvo, &niz[n].redni_broj) == 2){
        n++;
    }

    for(i = 1; i < n; i++){
        if((niz[i].redni_broj) == 1)
            continue;
        else if(strcmp(niz[i-1].srodstvo, niz[i].srodstvo) == 0) {
            broj_ponavljanja++;
            printf("Ponavljanje na liniji broj: %d\n", i);
        }
    }

    printf("\nBroj ponavljanja: %d\n", broj_ponavljanja);

    fclose(fin);
    return 0;
}
