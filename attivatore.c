#include "definizioni.h"
#include "libscissione.h"
#include <string.h>

extern int releaseSem(int, int, int, int);
extern int reserveSem(int, int, int, int);
extern void err_exit(char *);

int main(int agrc, char **argv){
    int semid = atoi(argv[0]);

    if(releaseSem(semid, 0, 1, 2) == -1)
        err_exit("releaseSem\n");
    printf("[attivatore %d] ho inizializzato, aspetto...\n", getpid());
    if(reserveSem(semid, 1, 1, 2) == -1)
        err_exit("reserveSem simulazione\n");
    printf("[attivatore] inizio anche io simulazione\n");
    exit(EXIT_SUCCESS);
}