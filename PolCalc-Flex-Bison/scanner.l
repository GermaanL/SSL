%option noyywrap
%{
#include "Calculator.tab.h"
%}
DIGITO      [0-9]
ENTERO      [-]?{DIGITO}+
FLOTANTE    {ENTERO}?[.]{DIGITO}?+
%%
[ \t]+      ;
{ENTERO}    |
{FLOTANTE}  { yylval.real = atof(yytext); return NUMBER;}
"+"         {return ADD;}
"*"         {return MUL;}
"-"         {return SUB;}
"/"         {return DIV;}
"\n"        {return POPRESULT;}
.           { yylval.lexError = yytext[0]; return LEXERROR; }
%%
