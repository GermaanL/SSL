#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "Graficador.h"

void print_char(char, int);
void valor_maximo(int *, int, int *, int *);
int valor_mediano(int *, int);
void ordenar_menor_a_mayor(int *, int);
int eliminar_repetidos(int*, int);
int calcular_con_escala(int, float);

// palabras [1,3,5,2,1,2] 1 de longitud 1, 3 de longitud 2, etc...

void graficar (int * palabras, int palabrasLength, Modo modo, float valorColMax) {
    int defaultMax = 0;
    int defaultMin = INT_MAX;
    int * valMax = &defaultMax;
    int * valMin = &defaultMin;

    valor_maximo(palabras, palabrasLength, valMax, valMin);
    int mediana = valor_mediano(palabras, palabrasLength);
    float escalaUp = 1;
    float escalaDown = 1;
    if (*valMax > valorColMax){
        if (valorColMax/2 - *valMax - mediana < 0){
            float diff = *valMax - mediana;
            escalaUp = valorColMax/2 / diff;
        }
        if (valorColMax/2 - mediana - *valMin < 0){
            float diff = mediana - *valMin;
            escalaDown = valorColMax/2 / diff;
        }
    }

    int width = (*valMax*escalaUp) + (*valMin*escalaDown);

    if (modo == HORIZONTAL){
        int padding = ((width + 4 - 23) / 2);
        if (padding < 0){
            padding = 0;
        }
        int paddingV = ((palabrasLength + 2 - 20) / 2);
        if (paddingV < 0){
            paddingV = 0;
        }
        paddingV += 20;
        padding += 23;
        char * vTitle = "<Cantidad de letras>";
        printf("%*s", padding, "<Cantidad de palabras>\n");
        printf("####HISTOGRAMA#");
        print_char('#', width - 11);
        printf("\n");

        for (int i = 0; i < palabrasLength; i++){
            printf("%2d", i+1);
            if (paddingV > i){
                printf(" ");
            }
            else{
                printf("%d", vTitle[i - paddingV]);
            }
            printf("#");
            if (palabras[i] < mediana){
                print_char('@', calcular_con_escala(palabras[i], escalaDown));
            }
            else{
                print_char('@', calcular_con_escala(palabras[i], escalaUp));
            }
            printf("\n");
        }
    }
    else{
        char * vTitle = "Cantidad de palabras";
        int h = 0;

        if (*valMax < mediana){
            h = *valMax*escalaDown;
        }
        else{
            h = *valMax*escalaUp;
        }
        for (int i = 0; i < h; i++){
            if (i + strlen(vTitle) + 1 > h){
                printf("%c", vTitle[h-i-1]);
            }
            else{
                printf(" ");
            }
            printf("#");

            for (int i2 = 0; i2 < palabrasLength; i2++){
                if (palabras[i2] < mediana){
                    int val = calcular_con_escala(palabras[i2], escalaDown);
                    if (val + i >= h){
                        printf("@");
                    }
                    else{
                        printf(" ");
                    }
                }
                else{
                    int val = calcular_con_escala(palabras[i2], escalaUp);
                    if (val + i >= h){
                        printf("@");
                    }
                    else{
                        printf(" ");
                    }
                }
            }
            printf("\n");
        }
        printf(" ");
        for (int i = 0; i <= palabrasLength; i++){
            printf("#");
        }
        printf("\n ");
        for (int i = 0; i <= palabrasLength; i++){
            int val = i/10;

            if (val == 0){
                printf(" ");
            }
            else{
                printf("%d", val);
            }
        }
        printf("\n  ");
        for (int i = 1; i <= palabrasLength; i++){
            printf("%d", i%10);
        }
        printf("\n");
    }
}

int calcular_con_escala(int valor, float escala){
    float resultado = valor*escala;

    if (resultado < 1 && resultado > 0){
        return 1;
    }
    return (int)ceil(resultado);
}

int eliminar_repetidos(int* arr, int length){
    int lastVal = -1;
    int noRepetidos = 0;
    int nuevoArr[length];
    for (int i = 0; i < length; i++){
        if (lastVal != arr[i]){
            lastVal = arr[i];
            nuevoArr[noRepetidos] = arr[i];
            noRepetidos++;
        }
    }
    arr = nuevoArr;
    return noRepetidos;
}

void print_char(char c, int n){
    if (n > 0){
     int i;
     for(i=0;i<n;i++)
         putchar(c);
    }
}

void valor_maximo(int * arr, int length, int * max, int * min){
    for(int i=0; i < length; i++){
        if (arr[i] > *max){
            *max = arr[i];
        }
        if (arr[i] < *min){
            *min = arr[i];
        }
    }
}

int valor_mediano(int * arr, int length){
    int arrValores[length];
    memcpy(arrValores, arr, sizeof(arrValores));
    ordenar_menor_a_mayor(arrValores, length);
    int hayado = 0;
    float pos = 0;
    float valoresUnicos = length;
    int valorPrevio = -1;
    int media = 0;

    for(int i=0; i < length && !hayado; i++){
        if (valorPrevio != arrValores[i]){
            valorPrevio = arrValores[i];
            pos += 1;
        }
        else{
            valoresUnicos -= 1;
        }
        if (pos >= valoresUnicos/2.0){
            hayado = 1;
            media = arrValores[i];
        }
    }
    return media;
}

void ordenar_menor_a_mayor(int * arr, int length){
    // burbujeo simple
    for(int i=0; i < length; i++){
        for(int i2=0; i2 < length - i - 1; i2++){
            if (arr[i2] > arr[i2 + 1]){
                int aux = arr[i2 + 1];
                arr[i2 + 1] = arr[i2];
                arr[i2] = aux;
            }
        }
    }
}

void print_arr(int* array){
   for(int loop = 0; loop < 10; loop++)
      printf("%d ", array[loop]);
    printf("\n");
}
