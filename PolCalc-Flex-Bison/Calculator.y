%{
#include <stdio.h>
#include <stdbool.h>
%}
%union 
{
        float real;
        char lexError;
}
%token <real> NUMBER 
%token ADD SUB MUL DIV
%token POPRESULT
%token <lexError> LEXERROR
%type <real> expresion

%%

cuenta: expresion POPRESULT
        { printf("Cuenta valida.\nResultado = %.2f", $1);}
        ;

expresion: NUMBER                       {$$ = $1; }
        | LEXERROR                      {printf("Error Lexico: '%c' no valido\n",$1); return 1; }
        | expresion expresion ADD       {$$ = $1 + $2;}
        | expresion expresion SUB       {$$ = $1 - $2;}
        | expresion expresion MUL       {$$ = $1 * $2;}
        | expresion expresion DIV       { if($2 != 0) $$ = $1 / $2; else {printf("Division por 0\n"); return 1;}}
        ;

%%

int main() {
    yyparse();
    return 0;
}

bool getNextToken() {
        
}

// float make_number(char * number) {
//         return atof(number);
// }

int yyerror(const char *msg) {
    printf("Error: %s\n", msg);
    return 1;
}
