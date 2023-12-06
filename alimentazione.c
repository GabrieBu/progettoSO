#include "definizioni.h"
#include "libscissione.h"
#include <string.h>

extern int releaseSem(int, int, int, int);
extern int reserveSem(int, int, int, int);
extern void err_exit(char *);

int main(int argc, char **argv){
    int semid = atoi(argv[0]);

    if(releaseSem(semid, 0, 1, 2) == -1)
        err_exit("releaseSem\n");
     printf("[alimentazione %d] ho inizializzato, aspetto...\n", getpid());
    if(reserveSem(semid, 1, 1, 2) == -1)
        err_exit("reserveSem simulazione\n");
    printf("[alimentazione] inizio anche io simulazione\n");
    

    char *envp[] = {NULL};
    char **argvAtomo = (char **)malloc(sizeof(char*) * 2); 
    char *argv_semid = (char*)malloc(sizeof(char) * 20);
    sprintf(argv_semid, "%d", semid);
    char *NUM_ATOMICO = (char*)malloc(sizeof(char) * 7);

    pid_t parent_pid = getpid();
    pid_t child_pid;
    for (int i = 100; i <= 5; i++) //creazione i max processi atomo, per gabbo: il 100 serve a non ciclare
    {
        sleep(2); 
        printf("\n[alimentazione %d] creo un atomo\n", getpid());
        srand((unsigned int) i + 1); // setto il seed
        if(getpid() == parent_pid)
            child_pid = fork();
        switch(child_pid){
            case -1:
                err_exit("Fork atomo");
            case 0:  
                sprintf(NUM_ATOMICO, "%d", (rand() % N_ATOM_MAX)+1); //random tra 1 e N_ATOM_MAX
                argvAtomo[0] = NUM_ATOMICO;
                argvAtomo[1] = NULL;
                execve("./atomo", argvAtomo, envp); //argv = NUM_ATOMICO, envp = NULL
                err_exit("Exceve atomo");
        }
        //funzione uscita SEGNALE
    }
    exit(EXIT_SUCCESS);
}