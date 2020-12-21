%top{
	#include <stdio.h>
	#include "parser.h"
}

%{
int errlex;
char msg[120];
%}

%option header-file="scanner.h"
%option outfile="scanner.c"
%option noinput
%option nounput
%option yylineno

Letra														[[:alpha:]]
Digito														[0-9]
Letra_Digito												[[:alnum:]]
Espacio														[[:space:]]
OperadorAsignacion											"<-"
Comentario													"##".*
Otros														[[:punct:]]{-}[();,+\-*/]

%%
programa 													return PROGRAMA;
declarar													return DECLARAR;
leer														return LEER;
escribir													return ESCRIBIR;
fin-prog													return FIN_PROG;
{Letra}{Letra_Digito}*										{yylval = strdup(yytext); return IDENTIFICADOR;}
{Digito}+													return CONSTANTE;
"("															return '(';
")"															return ')';
","															return ',';
"+"															return '+';
"-"															return '-';
"*"															return '*';
"/"															return '/';
";"															return ';';
{OperadorAsignacion} 										return ASIGNACION;
{Otros}+													{errlex++; sprintf(msg,"Error léxico: cadena desconocida: %s", yytext); yyerror(msg);}
{Letra}{Letra_Digito}*{Otros}+({Letra_Digito}|{Otros})*		{errlex++; sprintf(msg, "Error léxico: identificador inválido: %s", yytext); yyerror(msg);}
{Digito}+{Letra}+{Letra_Digito}*							{errlex++; sprintf(msg, "Error léxico: constante inválida: %s", yytext); yyerror(msg);}
{Espacio}+													|
{Comentario}												;
%%
