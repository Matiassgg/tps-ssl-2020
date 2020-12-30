%code top{
	#include <stdio.h>
	#include "scanner.h"
	#include "semantic.h"
	#include "symbol.h"		// ************************************
}

%code provides {
	void yyerror(const char *);
	extern int errlex; 				// Contador de errores lexicos
	extern int yynerrs;
	extern int errSemanticos;
}

%define api.value.type{char *}		// Registro semantico de tipo char*

%defines "parser.h"					
%output "parser.c"

%start programa						// Es el axioma de la gramatica sintactica
%define parse.error verbose       // Mas detalles al encontrar un error         // No me funciona el detailed, lo cambie a verbose

%token 	FDT PROGRAMA DECLARAR LEER ESCRIBIR FIN_PROG IDENTIFICADOR CONSTANTE ASIGNACION
//%token ASIGNACION "<-"

%left  '-'  '+'       	// Tienen menor precedencia , va "mas arriba"
%left  '*'  '/'       	// Tienen mas precedencia
%precedence NEG			// Es el cambio de contexto del operador (ahora unario) '-'

%%
// Lo cambié a recursión a izquierda porque bison se lleva mejor !!! aaaaaaaaaaaaaaaaaaaaaaaaa
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

// Informa la ocurrencia de un error en una determinada linea del fuente
void yyerror(const char *s){
		printf("\nlínea #%d  %s", yylineno, s);
}
