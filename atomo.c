#include "definizioni.h"
#include "libscissione.h"
#include <string.h>

extern int releaseSem(int, int, int, int);
extern int reserveSem(int, int, int, int);
extern void err_exit(char *);

int main(int argc, char **argv){
    int NUM_ATOMICO = atoi(argv[1]);
    char *num_a1_char;
    sprintf(num_a1_char, "%f", NUM_ATOMICO * 0.5);
    char *num_a2_char;
    sprintf(num_a2_char, "%f", NUM_ATOMICO - NUM_ATOMICO * 0.5);
    char *argv_figlio_1[2] = {NULL, num_a1_char};
    char *argv_figlio_2[2] = {NULL, num_a2_char};
    char *envp[1] = {NULL};

    printf("[pid(%d), atomo: %d]", getpid(), NUM_ATOMICO);
    //inizializzazione atomo
    if(argv[0] != NULL){
        int semid = atoi(argv[0]); //semid semaforo master (servirà sono nell'avvio della simulazione)
        if(releaseSem(semid, 0, 1, 2) == -1)
            err_exit("releaseSem inizializzazione");
        //fine inizializzazione
        printf("[attomo] ho inizializzato, aspetto...");
        //inizio simulazione
        if(reserveSem(semid, 1, 1, 2) == -1)
            err_exit("reserveSem simulazione");
        printf("[atomo] inizio anche io simulazione");
    }
   
    //inizio simulazione
    /*if(NUM_ATOMICO > MIN_N_ATOMICO){
        switch(fork()){
            case -1:
                err_exit("Fork atomo");
            case 0:
                execve("./atomo", argv_figlio_1, envp);
                err_exit("Errore execve atomo figlio 1\n");
            default:
                execve("./atomo", argv_figlio_2, envp);
                err_exit("Errore execve atomo figlio 2\n");
        }
    }
    else{
        printf("Non sono riuscito a forkare! dediocan: %d!!\n", NUM_ATOMICO);
    }*/

    exit(EXIT_SUCCESS);
}