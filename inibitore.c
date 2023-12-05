#include "definizioni.h"
#include "libscissione.h"
#include <string.h>

extern int releaseSem(int, int, int, int);
extern int reserveSem(int, int, int, int);
extern void err_exit(char *);

int main(int argc, char **argv){
    int semid = atoi(argv[0]);
    printf("Sono inibitore e semid: %d\n", semid);

    if(releaseSem(semid, 0, 1, 2) == -1)
        err_exit("releaseSem");
     printf("[inibitore] ho inizializzato, aspetto...");
     if(reserveSem(semid, 1, 1, 2) == -1)
        err_exit("reserveSem simulazione");
     printf("[inibitore] inizio anche io simulazione");
    exit(EXIT_SUCCESS);
}