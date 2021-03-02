#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc > 4){
        write(2, "Unijeli ste previše parametara\n", 32);
        exit(EXIT_FAILURE);
    }

    if(argc < 4){
        write(2, "Unijeli ste premalo parametara\n", 32);
        exit(EXIT_FAILURE);
    }

    int ulazna = open(argv[1], O_RDONLY);
    if (ulazna == -1) {
        write(2, "Greška prilikom otvaranja ulazne datoteke\n", 43);
        exit(EXIT_FAILURE);
    }

    int zastavice = O_CREAT | O_WRONLY | O_TRUNC;
    int dozvole = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    int izlazna = open(argv[2], zastavice, dozvole);
    if (izlazna == -1) {
        write(2, "Greška prilikom otvaranja izlazne datoteke\n", 44);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[3]);
    char buffer[n];

    size_t kolicina;
    while((kolicina = read(ulazna, buffer, sizeof(buffer))) > 0) {
        write(izlazna, buffer, kolicina);
    }
        close(ulazna);
        close(izlazna);

    return 0;
}
