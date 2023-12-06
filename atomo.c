#include "definizioni.h"
#include "libscissione.h"
#include <string.h>

extern int releaseSem(int, int, int, int);
extern int reserveSem(int, int, int, int);
extern void err_exit(char *);

int main(int argc, char **argv){
    int NUM_ATOMICO = atoi(argv[0]);
    int num_atomico_figlio_1 = NUM_ATOMICO * 0.5;
    int num_atomico_figlio_2 =  NUM_ATOMICO - num_atomico_figlio_1;

    char *num_a1_char = (char*)malloc(sizeof(char) * 20); //non so bene perchè 20, mi gustava
    sprintf(num_a1_char, "%d", num_atomico_figlio_1);
    char *num_a2_char = (char*)malloc(sizeof(char) * 20); //non so bene perchè 20, mi gustava
    sprintf(num_a2_char, "%d", num_atomico_figlio_2);

    char **argv_figlio_1 = (char**)malloc(sizeof(char*) * 2);
    char **argv_figlio_2 = (char**)malloc(sizeof(char*) * 2);
    argv_figlio_1[0] = num_a1_char;
    argv_figlio_1[1] = NULL;
    argv_figlio_2[0] = num_a2_char;
    argv_figlio_2[1] = NULL;
    //char *argv_figlio_1[2] = {num_a1_char, NULL};
    //char *argv_figlio_2[2] = {num_a2_char, NULL};
    char *envp[1] = {NULL};

    printf("[pid(%d), NUM_ATOMICO: %d]\n", getpid(), NUM_ATOMICO);
    //inizializzazione atomo
    if(argv[1] > 0){
        int semid = atoi(argv[1]); //semid semaforo master (servirà sono nell'avvio della simulazione)
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
                execve("./atomo", argv_figlio_1, envp);
                err_exit("Errore execve atomo figlio 1\n");
            default:
                execve("./atomo", argv_figlio_2, envp);
                err_exit("Errore execve atomo figlio 2\n");
        }
    }
    else
        printf("[atomo non più forkabile %d] NUM_ATOMICO: %d\n", getpid(), NUM_ATOMICO);
    

    exit(EXIT_SUCCESS);
}