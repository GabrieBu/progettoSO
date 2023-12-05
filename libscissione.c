#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>

int reserveSem(int semid, int semNum, int semOperation, int numSemafori){
    struct sembuf sops[numSemafori];

    sops[semNum].sem_num = semNum;
    sops[semNum].sem_op = (semOperation * -1);
    sops[semNum].sem_flg = 0;

    return semop(semid, &sops, numSemafori);
}

int releaseSem(int semid, int semNum, int semOperation, int numSemafori){
    struct sembuf sops[numSemafori];
    sops[semNum].sem_num = semNum;
    sops[semNum].sem_op = semOperation;
    sops[semNum].sem_flg = 0;

    return semop(semid, &sops, numSemafori);
}

void err_exit(char* s){
    printf("\nCausa errore: %s", s);
    exit(EXIT_FAILURE);
}