%code top{
	#include <stdio.h>
	#include "scanner.h"
	#include "semantic.h"
	#include "symbol.h"
}

%code provides {
	void yyerror(const char *);
	extern int errlex;
	extern int yynerrs;
	extern int errSemanticos;
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
// Lo cambié a recursión a izquierda porque sino las sentencias salen del último al primero !!! aaaaaaaaaaaaaaaaaaaaaaaaa
programa :			{Comenzar();}	PROGRAMA listaSentencias FIN_PROG {Terminar();}			{if (yynerrs || errlex || errSemanticos) YYABORT; else YYACCEPT;}
					;

listaSentencias :		sentencia 
					| 	sentencia listaSentencias
					;

sentencia :				LEER'('listaIdentificadores')'';'
					|	ESCRIBIR'('listaExpresiones')'';'
					|	DECLARAR IDENTIFICADOR ';' {Chequear($2);}
					|	identificador ASIGNACION expresion ';' {Asignar($1,$3);}
					|   error ';'
					;

listaIdentificadores :	identificador {Leer($1);}
					| 	listaIdentificadores ',' identificador {Leer($3);}
					;

listaExpresiones :		expresion {Escribir($1);}
				    | 	listaExpresiones ',' expresion {Escribir($3);}
					;
						
expresion:			 	expresion '+' expresion		{$$ = GenInfijo($1, '+', $3);}
                  	| 	expresion '-' expresion		{$$ = GenInfijo($1, '-', $3);}
                   	| 	expresion '*' expresion		{$$ = GenInfijo($1, '*', $3);}
                  	| 	expresion '/' expresion		{$$ = GenInfijo($1, '/', $3);}
			        | 	'-'valor %prec NEG		{$$ = GenUnario('-', $2);}
                   	| 	'('expresion')'
					|	valor
					;
                        
valor :					identificador
					|	CONSTANTE
					;
					
identificador:		IDENTIFICADOR {if(ProcesarId($1)) YYERROR;}
%%

int errlex = 0;

void yyerror(const char *s){
		printf("\nlínea #%d  %s", yylineno, s);
}
