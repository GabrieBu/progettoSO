#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// TERMINAZIONE
#define SIM_DURATION 10
//----------------------
// INIZIALIZZAZIONE
#define N_ATOMI_INIT 5
#define N_ATOM_MAX 30
//----------------------
//GENERALI
#define ENERGY_DEMAND 15
#define STEP_NANO 0.000000999 //999 nanosecondi -> 0.000000999 secondi
#define MIN_N_ATOMICO 10
#define MSG_SIZE_IDENT 128

//DECOMMENTATE
/*union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    #if defined(__linux__)
    struct seminfo *__buf;
    #endif
};*/ 

struct msgbuf{
    long mtype;
    char mtext[MSG_SIZE_IDENT];
};
//----------------------
