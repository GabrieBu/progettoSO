#include "definizioni.h"
#include "libscissione.h"
#include <string.h>

extern int releaseSem(int, int, int, int);
extern int reserveSem(int, int, int, int);
extern void err_exit(char *);

int main(int agrc, char **argv){
    printf("Sono attivatore e semid: %s\n", argv[0]);
    int semid = atoi(argv[0]);

    if(releaseSem(semid, 0, 1, 2) == -1)
        err_exit("releaseSem");
    printf("[attivatore] ho inizializzato, aspetto...");
    if(reserveSem(semid, 1, 1, 2) == -1)
        err_exit("reserveSem simulazione");
    printf("[attivatore] inizio anche io simulazione");
    exit(EXIT_SUCCESS);
}