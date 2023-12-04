#include "definizioni.h"

int main(int argc, char **argv){
    printf("Sono atomo [%d] e il mio NUM_ATOMICO: %s\n", getpid(), argv[0]);
    exit(EXIT_SUCCESS);
}