%top{
	#include <stdio.h>
	#include "parser.h"
	int errlex;
	char buffer[200];
}

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
{Letra}{Letra_Digito}*										{yylval = strdup(yytext);return IDENTIFICADOR;}
{Digito}+													{yylval = strdup(yytext);return CONSTANTE;}
"("															return '(';
")"															return ')';
","															return ',';
"+"															return '+';
"-"															return '-';
"*"															return '*';
"/"															return '/';
";"															return ';';
{OperadorAsignacion} 										return ASIGNACION;
{Otros}+													{sprintf(buffer,"Error léxico: cadena desconocida: %s",yytext);yyerror(buffer);errlex++;}
{Letra}{Letra_Digito}*{Otros}+({Letra_Digito}|{Otros})*		{sprintf(buffer,"Error léxico: identificador inválido: %s",yytext);yyerror(buffer);errlex++;};		
{Digito}+{Letra}+{Letra_Digito}*							{sprintf(buffer,"Error léxico: constante inválida: %s",yytext);yyerror(buffer);errlex++;};
{Espacio}+													|
{Comentario}												;
%%
