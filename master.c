#include "definizioni.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include "libscissione.h"

extern int releaseSem(int, int, int, int);
extern int reserveSem(int, int, int, int);
extern void err_exit(char *);

void init_processi(pid_t parent_pid, pid_t child_pid, int semid){
    char *semidChar;
    sprintf(semidChar, "%d", semid);
    char *envp[] = {NULL};
    char *argvNull[2] = {semidChar, NULL};

     switch(fork()){ //creazione attivatore
        case -1:
            err_exit("Fork attivatore");
        case 0:
            execve("./attivatore", argvNull, envp);
            err_exit("Exceve attivatore");
    }
    
    switch(fork()){ //creazione alimentazione
        case -1:
            err_exit("Fork attivatore");
        case 0:
            execve("./alimentazione", argvNull, envp);
            err_exit("Exceve alimentazione");
    }

    switch(fork()){ //creazione inibitore
        case -1:
            err_exit("Fork attivatore");
        case 0:
            execve("./inibitore", argvNull, envp);
            err_exit("Exceve inibitore");
    }
    char **argvAtomo = (char **)malloc(sizeof(char*) * 2); 
    char *argv_key = (char*)malloc(sizeof(char) * 20);
    sprintf(argv_key, "%d", semid);
    char *NUM_ATOMICO = (char*)malloc(sizeof(char) * 7);
    for(int i = 0; i < N_ATOMI_INIT; i++){ //creazione N_ATOMI_INIT processi atomo
         srand((unsigned int) i); // setto il seed
        if(getpid() == parent_pid)
            child_pid = fork();
        
        switch(child_pid){
            case -1:
                err_exit("Fork atomo");
            case 0:  
                sprintf(NUM_ATOMICO, "%d", (rand() % N_ATOM_MAX) + 1); //random tra 1 e N_ATOM_MAX
                argvAtomo[0] = argv_key;
                argvAtomo[1] = NUM_ATOMICO;
                execve("./atomo", argvAtomo, envp); //argv = NUM_ATOMICO, envp = NULL
                err_exit("Exceve atomo");
        }
    }
    free(argvAtomo);
    free(NUM_ATOMICO);
    free(argv_key);
}

void print_stats(){
    //stamperemo le stats
}

int main(){
    pid_t master_pid = getpid(), child_pid;
    int semid; //semid semafoto master
    int key = ftok("master.c", 'A');
    union semun arg_inizializzazione;
    arg_inizializzazione.val = 0; //inizializzo semaforo inizializzazione a 0
    union semun arg_simulazione;
    arg_simulazione.val = 0; //inizializzo semaforo simulazione a N_ATOMI_INIT + 3
    
    printf("[master %d]\n", master_pid);

    if((semid = semget(key, 2, IPC_CREAT | 0666 )) == -1)
        err_exit("Semget");

    if(semctl(semid, 0, SETVAL, arg_inizializzazione) == -1) //inizializzo semaforo inizializzazzione a 0
        err_exit("semctl con SETVAL");
    
    if(semctl(semid, 1, SETVAL, arg_simulazione) == -1) //inizializzo semaforo inizializzazzione a 0
        err_exit("semctl con SETVAL");

    init_processi(master_pid, child_pid, semid); //inizializza tutti i processi

    int semaph_operation = N_ATOMI_INIT + 3;
    if(reserveSem(semid, 0, semaph_operation, 2) == -1)
        err_exit("reserveSem");

    printf("\n[master %d] fine inizializzazione, inizia la simulazione\n", getpid());
    //inizio simulzione
    if(releaseSem(semid, 1, semaph_operation, 2) == -1)
        err_exit("releaseSem simulazione");
    

    if(semctl(semid, 0, IPC_RMID, NULL) == -1)
        err_exit("remove semid_inizializzazione IPC_RMID");
     if(semctl(semid, 1, IPC_RMID, NULL) == -1)
        err_exit("remove semid_simulazione IPC_RMID");
    exit(EXIT_SUCCESS);
}