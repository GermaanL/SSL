#include <stdint.h>
#include <stdio.h> 
#include <time.h>
#include "histograma.h"

/// Convert seconds to nanoseconds
#define SEC_TO_NS(sec) ((sec)*1000000000)
#define MAX_LONGITUD_PALABRA 15

uint64_t get_time(void){
    uint64_t nanoseconds;
    struct timespec ts;
    int return_code = timespec_get(&ts, TIME_UTC);
    if (return_code == 0)
    {
        printf("Failed to obtain timestamp.\n");
        nanoseconds = UINT64_MAX;
    }
    else
    {
        nanoseconds = SEC_TO_NS((uint64_t)ts.tv_sec) + (uint64_t)ts.tv_nsec;
    }

    return nanoseconds;
}


int main (int argc, char *argv[]) {
    int palabras[MAX_LONGITUD_PALABRA] = {0};
    uint64_t start = get_time();
    crear_histograma(stdin, palabras, MAX_LONGITUD_PALABRA);
    uint64_t stop = get_time();

    if (start == UINT64_MAX || stop == UINT64_MAX){
        return 1;
    }
    uint64_t duration = stop - start;
    printf("Duracion de la ejecucion: %ld.%ld s.\n", duration/1000000000, duration%1000000000);
    return 0;
}