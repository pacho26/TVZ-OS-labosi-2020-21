#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc > 4){
        printf("Unijeli ste previše parametara!");
        exit(1);
    }

    if(argc < 4){
        printf("Unijeli ste premalo parametara!");
        exit(1);
    }

    FILE *ulazna = fopen(argv[1], "r");
    if(ulazna == NULL)
    {
        printf("Greška prilikom otvaranja ulazne datoteke!\n");
        exit(1);
    }

    FILE *izlazna = fopen(argv[2], "w");

    int n = atoi(argv[3]);
    char buffer[n];

    size_t kolicina;
    while((kolicina = fread(buffer, 1, sizeof(buffer), ulazna)) > 0)
    {
        fwrite(buffer, 1, kolicina, izlazna);
    }

    fclose(ulazna);
    fclose(izlazna);

    return 0;
}
