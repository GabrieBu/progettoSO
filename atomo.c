#include "definizioni.h"
#include "libscissione.h"
#include <string.h>

extern int releaseSem(int, int, int, int);
extern int reserveSem(int, int, int, int);
extern void err_exit(char *);

int main(int argc, char **argv){
    int NUM_ATOMICO = atoi(argv[1]);
    char *prova = "qa";
    char *num_a1_char = (char*)malloc(sizeof(char) * 20);
    sprintf(num_a1_char, "%f", NUM_ATOMICO * 0.5);
    char *num_a2_char = (char*)malloc(sizeof(char) * 20);
    sprintf(num_a2_char, "%f", NUM_ATOMICO - NUM_ATOMICO * 0.5);
    char *argv_figlio_1[3] = {prova, num_a1_char, NULL};
    char *argv_figlio_2[3] = {prova, num_a2_char, NULL};
    char *envp[1] = {NULL};

    printf("[pid(%d), NUM_ATOMICO: %d]\n", getpid(), NUM_ATOMICO);
    //inizializzazione atomo
    if(argv[0] != NULL){
        int semid = atoi(argv[0]); //semid semaforo master (servirà sono nell'avvio della simulazione)
        if(releaseSem(semid, 0, 1, 2) == -1)
            err_exit("releaseSem inizializzazione\n");
        //fine inizializzazione
        printf("[atomo] ho inizializzato, aspetto...\n");
        //inizio simulazione
        if(reserveSem(semid, 1, 1, 2) == -1)
            err_exit("reserveSem simulazione\n");
        printf("[atomo] inizio anche io simulazione\n");
    }
   
    //inizio simulazione
    if(NUM_ATOMICO > MIN_N_ATOMICO){
        switch(fork()){
            case -1:
                err_exit("Fork atomo");
            case 0:
                printf("[atomo forkato %d]", getpid());
                execve("./atomo", argv_figlio_1, envp);
                err_exit("Errore execve atomo figlio 1\n");
            default:
                printf("[atomo forkato %d]", getpid());
                execve("./atomo", argv_figlio_2, envp);
                err_exit("Errore execve atomo figlio 2\n");
        }
    }
    else{
        printf("[atomo non più forkabile %d] NUM_ATOMICO: %d\n", getpid(), NUM_ATOMICO);
    }

    exit(EXIT_SUCCESS);
}