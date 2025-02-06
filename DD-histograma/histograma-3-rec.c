#include <stdio.h>
#include "histograma.h"

void estado_out(FILE *in, int longitudes[], int max_long, int longitud);
void estado_in(FILE *in, int longitudes[], int max_long, int longitud);

void crear_histograma(FILE *in, int longitudes[], int max_long) {
    printf("Creando Histograma con recursion\n");
    estado_out(in, longitudes, max_long, -1);
}

void estado_out(FILE *in, int longitudes[], int max_long, int longitud) {
    int c;
    c=getc(in);
    if (c != EOF) {
        if (c != ' ' && c != '\n' && c != '\t') {
            estado_in(in, longitudes, max_long, longitud + 1);
        } else {
            estado_out(in, longitudes, max_long, longitud);
        }
    }
    else if (longitud != -1){
        longitudes[longitud]++;
    }
}

void estado_in(FILE *in, int longitudes[], int max_long, int longitud) {
    int c;
    c = getc(in);
    if (c != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            longitudes[longitud]++;
            estado_out(in, longitudes, max_long, -1);
        } else {
            estado_in(in, longitudes, max_long, longitud + 1);
        }
    }
    else if (longitud != -1){
        longitudes[longitud]++;
    }
}