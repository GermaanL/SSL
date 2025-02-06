#include <stdio.h>
#include "histograma.h"

typedef enum{
    OUT,
    IN
} State;

void crear_histograma(FILE * in, int longitudes[], int max_long) {
    printf("Creando Histograma con enum switch\n");
    int longitud = -1;
    State state = OUT;

    for (int c; (c = getc(in)) != EOF;){
        switch (c){
            case ' ' :
            case '\n':
            case '\t':
                switch(state){
                    case IN:
                        switch (longitud > max_long){
                            case 1:
                                longitud = max_long;
                        }
                        longitudes[longitud]++;
                        longitud=-1;
                        state = OUT;
                }
            break;
            default: 
                switch(state){
                    case OUT:
                        state = IN;
                    case IN:
                        longitud++;
                }
        }
    }
    if (longitud != -1){
        longitudes[longitud]++;
    }
}

