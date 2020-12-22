%code top{
	#include <stdio.h>
	#include "scanner.h"
}

%code provides {
	void yyerror(const char *);
	extern int errlex; 				// Contador de errores lexicos
	extern int yynerrs;
}

%define api.value.type{char *}		// Registro semantico de tipo char*

%defines "parser.h"					
%output "parser.c"

%start todo						// Es el axioma de la gramatica sintactica
%define parse.error verbose       // Mas detalles al encontrar un error         // No me funciona el detailed, lo cambie a verbose

%token 	FDT PROGRAMA DECLARAR LEER ESCRIBIR FIN_PROG IDENTIFICADOR CONSTANTE ASIGNACION
//%token ASIGNACION "<-"

%left  '-'  '+'       	// Tienen menor precedencia , va "mas arriba"
%left  '*'  '/'       	// Tienen mas precedencia
%precedence NEG			// Es el cambio de contexto del operador (ahora unario) '-'

%%
// Lo dejo con recursion a derecha la gramatica o la cambio a izquierda porque bison se lleva mejor ??? aaaaaaaaaaaaaaaaaaaaaaaaa
todo	:				programa							{if (yynerrs || errlex) YYABORT;}
					;
					
programa :				PROGRAMA listaSentencias FIN_PROG
					;

listaSentencias :		sentencia 
					| 	sentencia listaSentencias
					;

sentencia :				LEER'('listaIdentificadores')'';'		    {printf("leer\n");} 
					|	ESCRIBIR'('listaExpresiones')'';'			{printf("escribir\n");} 
					|	DECLARAR IDENTIFICADOR';'				    {printf("declarar %s\n", $IDENTIFICADOR);} 		// Falta el lexema del identificador de la declaracion
					|	IDENTIFICADOR ASIGNACION expresion';'		{printf("asignación \n");}
					|   error ';'
					;

listaIdentificadores :	IDENTIFICADOR 								
					| 	IDENTIFICADOR','listaIdentificadores
					;

listaExpresiones :		expresion
				    | 	expresion','listaExpresiones
					;
						
expresion:			  	valor
			        | 	'-'valor %prec NEG							{printf("inversión\n");}
                   	| 	'('expresion')' 							{printf("paréntesis\n");}
                    | 	expresion '+' expresion 					{printf("suma\n");}
                  	| 	expresion '-' expresion 					{printf("resta\n");}
                   	| 	expresion '*' expresion 					{printf("multiplicación\n");}
                  	| 	expresion '/' expresion 					{printf("división\n");}
					;
                        
valor :					IDENTIFICADOR
					|	CONSTANTE
					;
%%

int errlex = 0;

// Informa la ocurrencia de un error en una determinada linea del fuente
void yyerror(const char *s){
		printf("línea #%d  %s\n", yylineno, s);
}
