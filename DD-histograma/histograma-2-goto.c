#include <stdio.h>
#include "histograma.h"

void crear_histograma(FILE * in, int longitudes[], int max_long) {
    printf("Creando Histograma con goto\n");
    int longitud = -1;
    int c;

    loop_start:
        c = getc(in);
        if (c != EOF) {
            if (c == ' ' || c == '\n' || c == '\t') {
                goto out;
            } else {
                longitud++;
                goto in;
            }
        }

    out:
        c = getc(in);
        if (c != EOF) {
            if (c == ' ' || c == '\n' || c == '\t') {
                goto out;
            } else {
                longitud++;
                goto in;
            }
        }
        else if (longitud != -1){
            longitudes[longitud]++;
        }

    in:
        c = getc(in);
        if (c != EOF) {
            if (c == ' ' || c == '\n' || c == '\t') {
                longitudes[longitud]++;
                longitud = -1;
                goto out;
            } else {
                longitud++;
                goto in;
            }
            goto loop_start;
        }
        else if (longitud != -1){
            longitudes[longitud]++;
        }
}