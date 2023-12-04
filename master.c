#ifndef DEFINIZIONI_H
#include "definizioni.h"
#endif

void err_exit(char* s){
    printf("\nCausa errore: %s", s);
    exit(EXIT_FAILURE);
}

void init_processi(pid_t parent_pid, pid_t child_pid){
    
     switch(fork()){ //creazione attivatore
        case -1:
            err_exit("Fork attivatore");
        case 0:
            execve("./attivatore", NULL, NULL);
            err_exit("Exceve attivatore");
        default: 
            wait(NULL);
    }
    
    switch(fork()){ //creazione alimentazione
        case -1:
            err_exit("Fork attivatore");
        case 0:
            execve("./alimentazione", NULL, NULL);
            err_exit("Exceve alimentazione");
         default: 
            wait(NULL);
    }

    switch(fork()){ //creazione inibitore
        case -1:
            err_exit("Fork attivatore");
        case 0:
            execve("./inibitore", NULL, NULL);
            err_exit("Exceve inibitore");
        default: 
            wait(NULL);
    }
    char **argvAtomo = (char **)malloc(sizeof(char*) * 1); 
    char* NUM_ATOMICO = (char*)malloc(sizeof(char) * 7);
    for(int i = 0; i < N_ATOMI_INIT; i++){ //creazione N_ATOMI_INIT processi atomo
        if(getpid() == parent_pid){
            child_pid = fork();
            srand((unsigned int) i); // setto il seed
        }
        switch(child_pid){
            case -1:
                err_exit("Fork atomo");
            case 0:  
                sprintf(NUM_ATOMICO, "%d", rand() % 30);
                argvAtomo[0] = NUM_ATOMICO;
                execve("./atomo", argvAtomo, NULL); //argv = NUM_ATOMICO, envp = NULL
                err_exit("Exceve atomo");
            default: 
                wait(NULL);
            }
    }
    free(argvAtomo);
    free(NUM_ATOMICO);
}

void print_stats(){
    //stamperemo le stats
}

int main(){
    pid_t master_pid = getpid(), child_pid;
    printf("[master %d]\n", master_pid);

    init_processi(master_pid, child_pid); //inizializza tutti i processi
    printf("\n[master %d] arriva qui\n", getpid());
    exit(EXIT_SUCCESS);
}