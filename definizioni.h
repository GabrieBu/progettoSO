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
#define N_ATOMI_INIT 10
#define N_ATOM_MAX 30
//----------------------
//GENERALI
#define ENERGY_DEMAND 15
#define STEP_NANO 0.000000999 //999 nanosecondi -> 0.000000999 secondi
#define MIN_N_ATOMICO 10

//----------------------
