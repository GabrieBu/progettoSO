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
#define STEP_NANO 0.000005 //500 nanosecondi
#define MIN_N_ATOMICO 10
//----------------------
