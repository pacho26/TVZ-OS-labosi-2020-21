#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#include <sys/types.h>

char polje_znakova[100000] ;

int main(void) {
    srand(time(NULL));
    
    for(int i = 1; i <= sizeof(polje_znakova); i++){
        int tmp = rand() % 2;
        if(tmp == 0)
            polje_znakova[i] = 1;
        else
            polje_znakova[i] = -1;
    }

    printf("PID od ovog procesa: %ld\n", getpid());

    for(int i = 1; i <= sizeof(polje_znakova); i++)
        printf("%d", polje_znakova[i]);

    sleep(5);
    return 0;
}