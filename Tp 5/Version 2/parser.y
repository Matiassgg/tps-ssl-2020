%code top{
	#include <stdio.h>
	#include "scanner.h"
	#include "symbol.h"
	#include "semantic.h"
}

%code provides {
	void yyerror(const char*);
	extern int errlex;
	extern int yynerrs;
	extern int errsemtc;
}

%defines "parser.h"					
%output "parser.c"

%define api.value.type{char *}
%define parse.error verbose

%start programa

%token FDT PROGRAMA DECLARAR LEER ESCRIBIR FIN_PROG IDENTIFICADOR CONSTANTE
%token ASIGNACION "<-"

%left  '-'  '+'
%left  '*'  '/'
%precedence NEG

%%

programa 				: {comenzar();} PROGRAMA listaSentencias FIN_PROG {finalizar();} {if(yynerrs || errlex || errsemtc) YYABORT; else YYACCEPT;}
						;

listaSentencias 		: %empty 
						| sentencia listaSentencias
						;

sentencia 				: LEER'('listaIdentificadores')'';'			
						| ESCRIBIR'('listaExpresiones')'';'					
						| DECLARAR IDENTIFICADOR';'							{if(declarar($2,4)) YYERROR;}					
						| identificador "<-"expresion';'					{asignar($3,$1);}
						| error';'
						;

listaIdentificadores 	: identificador 									{leer($1);}
						| listaIdentificadores','identificador				{leer($3);}
						;

listaExpresiones 		: expresion 										{escribir($1);}
						| listaExpresiones','expresion						{escribir($3);}
						;
						
expresion				: valor			
						| '-'valor %prec NEG								{$$ = generarUnario($2);}				
						| '('expresion')'									{$$ = $2;}
                        | expresion '+' expresion 							{$$ = generarInfijo($1,'+',$3);}
                        | expresion '-' expresion 							{$$ = generarInfijo($1,'-',$3);}
                        | expresion '*' expresion 							{$$ = generarInfijo($1,'*',$3);}
                        | expresion '/' expresion 							{$$ = generarInfijo($1,'/',$3);}									
                        ;
                        
valor 					: identificador										
						| CONSTANTE
						;
identificador			: IDENTIFICADOR										{if(verificarIdentificador($1)) YYERROR;}
						;

%%
// Informa la ocurrencia de un error en un determinada linea del fuente
void yyerror(char const *mensaje){
        printf("línea #%d: %s\n",yylineno,mensaje);
}
