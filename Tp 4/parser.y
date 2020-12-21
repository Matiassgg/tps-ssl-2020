%code top{
	#include <stdio.h>
	#include "scanner.h"
}

%code provides {
	void yyerror(const char *);
	extern int errlex;
	extern int yynerrs;
}

%define api.value.type{char *}

%defines "parser.h"					
%output "parser.c"

%start programa
%define parse.error verbose

%token 	FDT PROGRAMA DECLARAR LEER ESCRIBIR FIN_PROG IDENTIFICADOR CONSTANTE
%token ASIGNACION "<-"

%left  '-'  '+'
%left  '*'  '/'	
%precedence NEG	

%%						
programa :				PROGRAMA listaSentencias FIN_PROG {if (yynerrs || errlex) YYABORT;};

listaSentencias :		sentencia 
					| 	sentencia listaSentencias;

sentencia :				LEER'('listaIdentificadores')'';'		    {printf("leer\n");} 
					|	ESCRIBIR'('listaExpresiones')'';'			{printf("escribir\n");} 
					|	DECLARAR IDENTIFICADOR';'				    {printf("declarar %s\n", $IDENTIFICADOR);}
					|	IDENTIFICADOR ASIGNACION expresion';'		{printf("asignación \n");}
					|   error ';'

listaIdentificadores :	IDENTIFICADOR 								
					| 	IDENTIFICADOR','listaIdentificadores;

listaExpresiones :		expresion
				    | 	expresion','listaExpresiones;
						
expresion:			  	valor
			        | 	'-'valor %prec NEG							{printf("inversión\n");}
                   	| 	'('expresion')' 							{printf("paréntesis\n");}
                    | 	expresion '+' expresion 					{printf("suma\n");}
                  	| 	expresion '-' expresion 					{printf("resta\n");}
                   	| 	expresion '*' expresion 					{printf("multiplicación\n");}
                  	| 	expresion '/' expresion 					{printf("división\n");};
                        
valor :					IDENTIFICADOR
					|	CONSTANTE
%%
int errlex = 0;

// Informa la ocurrencia de un error en una determinada linea del fuente
void yyerror(const char *s){
		printf("línea #%d:  %s\n", yylineno, s);
}
