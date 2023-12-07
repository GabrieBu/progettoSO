#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <errno.h>
#include "libscissione.h"
#include "definizioni.h"

extern int releaseSem(int, int, int, int);
extern int reserveSem(int, int, int, int);
extern void err_exit(char *);


void init_processi(pid_t parent_pid, pid_t child_pid, int semid, int msgid){
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
    char **argvAtomo = (char **)malloc(sizeof(char*) * 3); 
    char *argv_semid = (char*)malloc(sizeof(char) * 20);
    sprintf(argv_semid, "%d", semid);
     char *argv_msgid = (char*)malloc(sizeof(char) * 20);
    sprintf(argv_msgid, "%d", msgid);
    char *NUM_ATOMICO = (char*)malloc(sizeof(char) * 7);
    for(int i = 0; i < N_ATOMI_INIT; i++){ //creazione N_ATOMI_INIT processi atomo
        srand((unsigned int) i + 1); // setto il seed
        if(getpid() == parent_pid)
            child_pid = fork();
        
        switch(child_pid){
            case -1:
                err_exit("Fork atomo");
            case 0:  
                sprintf(NUM_ATOMICO, "%d", (rand() % N_ATOM_MAX)+1); //random tra 1 e N_ATOM_MAX
                argvAtomo[0] = NUM_ATOMICO;
                argvAtomo[1] = argv_msgid;
                argvAtomo[2] = argv_semid;
                execve("./atomo", argvAtomo, envp); //argv = NUM_ATOMICO, envp = NULL
                err_exit("Exceve atomo");
        }
    }
    free(argvAtomo);
    free(NUM_ATOMICO);
    free(argv_semid);
}

void print_stats(){
    //stamperemo le stats
}

void print_msg_indentificazioni(struct msgbuf *msg_identificazione){
    printf("\n-mtype: %ld", msg_identificazione->mtype);
    printf("\n-mtext: %s\n", msg_identificazione->mtext);
}

int main(){
    pid_t master_pid = getpid(), child_pid;
    int semid, msgid; //semid semafoto master
    union semun arg_inizializzazione;
    arg_inizializzazione.val = 0; //inizializzo semaforo inizializzazione a 0
    union semun arg_simulazione;
    arg_simulazione.val = 0; //inizializzo semaforo simulazione a N_ATOMI_INIT + 3
    
    printf("[master %d]\n", master_pid);

    if((semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666 )) == -1)
        err_exit("Semget\n");

    if(semctl(semid, 0, SETVAL, arg_inizializzazione) == -1) //inizializzo semaforo inizializzazzione a 0
        err_exit("semctl con SETVAL\n");
    
    if(semctl(semid, 1, SETVAL, arg_simulazione) == -1) //inizializzo semaforo inizializzazzione a 0
        err_exit("semctl con SETVAL\n");

    if((msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666 )) == -1)
        err_exit("Msgget\n");

    init_processi(master_pid, child_pid, semid, msgid); //inizializza tutti i processi

    int semaph_operation = N_ATOMI_INIT + 3;
    if(reserveSem(semid, 0, semaph_operation, 2) == -1)
        err_exit("reserveSem\n");

    printf("\n[master %d] fine inizializzazione, inizia la simulazione\n", getpid());
    //inizio simulzione
    if(releaseSem(semid, 1, semaph_operation, 2) == -1)
        err_exit("releaseSem simulazione\n");
    
    sleep(5);
    if(semctl(semid, 0, IPC_RMID, NULL) == -1) //elimino il semaforo
        err_exit("remove semid_inizializzazione con IPC_RMID\n");
    //prima di rimuovere checko se tutti si identificano bene
    struct msgbuf lettura_identificazione;
    int error_msgrcv;
    printf("------MESSAGGI------");
   
     while( (error_msgrcv = msgrcv(msgid, &lettura_identificazione, MSG_SIZE_IDENT, 1, MSG_NOERROR | IPC_NOWAIT)) != -1){
        print_msg_indentificazioni(&lettura_identificazione);
     }
     if(error_msgrcv == -1){ //se ha dato errore la msgrcv
        if(errno != ENOMSG) //se l'errore è diverso da "non ci sono più messaggi"
            err_exit("failure msgrcv"); //esci
     }
    
    if(msgctl(msgid, IPC_RMID, NULL) == -1) //elimino la coda di messaggi
        err_exit("remove msg_identificazine con IPC_RMID\n");
    exit(EXIT_SUCCESS);
}