#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "histograma.h"

typedef enum{
    OUT,
    IN
} State;

// StateSetter Class
typedef struct StateSetter {
  State state;
  State (*setState)(struct StateSetter * this, char c);
  State (*getState)(struct StateSetter * this);
} StateSetter;

State stateSetter_setState(StateSetter * this, char c){
    if (c == ' ' || c == '\n' || c == '\t'){
        this->state = OUT;
    }
    else {
        this->state = IN;
    }

    return this->state;
}

State stateSetter_getState(StateSetter * this){
    return this->state;
}

StateSetter * stateSetter() {
    StateSetter * ssc = malloc(sizeof(StateSetter));
    ssc->state = OUT;
    ssc->setState = stateSetter_setState;
    ssc->getState = stateSetter_getState;
    return ssc;
}

// WordCounter Class
typedef struct WordCounter {
  StateSetter * stateSetter;
  int * (*count)(struct WordCounter * this, int max_length, char * text);
} WordCounter;

int * wordCounter_count(WordCounter * this, int max_length, char * text){
    int * word_lengths = calloc(max_length, sizeof(int));
    State prev_state = this->stateSetter->getState(this->stateSetter);
    int state_in_row_count = 0;
    
    if (prev_state == IN){
        state_in_row_count++;
    }
    for (int i = 0; i < strlen(text); i++){
        State current_state = this->stateSetter->setState(this->stateSetter, text[i]);

        if (current_state == IN){
            state_in_row_count++;
        }

        if (current_state == OUT && prev_state == IN){
            if (max_length < state_in_row_count){
                state_in_row_count = max_length;
            }
            word_lengths[state_in_row_count - 1]++;
            state_in_row_count = 0;
        }
        prev_state = current_state;
    }
    if (state_in_row_count > 0){
        if (max_length < state_in_row_count){
            state_in_row_count = max_length;
        }
        word_lengths[state_in_row_count - 1]++;
    }
    return word_lengths;
}

WordCounter * wordCounter() {
    WordCounter * wc = malloc(sizeof(WordCounter));
    wc->stateSetter = stateSetter();
    wc->count = wordCounter_count;
    return wc;
}

// WordReader Class
typedef struct WordReader {
  FILE * in;
  char * (*read)(struct WordReader * this);
} WordReader;

char * wordReader_read(WordReader * this){
    int prevBuffSize = 0;
    int currBuffSize = 1000;
    char * buffer = malloc((currBuffSize + 1) * sizeof(char));
    int c;
    int done = 0;
    for (int ib = 0; !done; ib++) {
        int i = prevBuffSize;
        while((c = getc(this->in)) != EOF && i < currBuffSize){
            buffer[prevBuffSize] = (char)c;
            i++;
        }
        if (c == EOF){
            done = 1;
            buffer[currBuffSize + 1] = '\0';
        }
        else{
            buffer = realloc(buffer, ((currBuffSize * 2) + 1) * sizeof(char));
        }
    }
        
    return buffer;
}

WordReader * wordReader(FILE * in) {
    WordReader * wr = malloc(sizeof(WordReader));
    wr->in = in;
    wr->read = wordReader_read;
    return wr;
}

void crear_histograma(FILE * in, int longitudes[], int max_long) {
    printf("Creando Histograma con objetos\n");
    WordCounter * wc = wordCounter();
    WordReader * wr = wordReader(in);
    char * text = wr->read(wr);
    int * count = wc->count(wc, max_long, text);
    // copy result
    for (int i = 0; i < max_long; i++){
        longitudes[i] = count[i];
    }
}