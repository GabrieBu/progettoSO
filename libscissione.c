#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>

int reserveSem(int semid, int semNum, int semOperation, int numSemafori){
    struct sembuf sops[numSemafori];

   for(int i = 0; i < numSemafori; i++){
        sops[i].sem_num = i;
        sops[i].sem_op = (i == semNum) ? (semOperation*-1) : 0;
        sops[i].sem_flg = 0;
   }
    
    return semop(semid, sops, numSemafori);
}

int releaseSem(int semid, int semNum, int semOperation, int numSemafori){
    struct sembuf sops[numSemafori];

    for(int i = 0; i < numSemafori; i++){
        sops[i].sem_num = i;
        sops[i].sem_op = (i == semNum) ? semOperation : 0;
        sops[i].sem_flg = 0;
   }

    return semop(semid, sops, numSemafori);
}

void err_exit(char* s){
    printf("\nCausa errore: %s", s);
    exit(EXIT_FAILURE);
}