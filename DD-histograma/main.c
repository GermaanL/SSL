#include <stdio.h>
#include "histograma.h"
#include "Graficador.h"

#define MAX_LONGITUD_PALABRA 15

int main (int argc, char *argv[]) {
    Modo modo = HORIZONTAL;

    if (argc == 2 && argv[1][0] == 'V'){
        modo = VERTICAL;
    }
    int palabras[MAX_LONGITUD_PALABRA] = {0};
    
    crear_histograma(stdin, palabras, MAX_LONGITUD_PALABRA);
    graficar(palabras, MAX_LONGITUD_PALABRA, modo, 30);

    return 0;
}