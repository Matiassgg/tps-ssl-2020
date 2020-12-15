%{
	#include <stdio.h>
	#include "scanner.h"
	void yyerror(const char *);
%}


%code provides {
	extern int errlex; 				// Contador de errores lexicos
}

%define api.value.type{char *}		// Registro semantico de tipo char*

%defines "parser.h"					
%defines "parser.c"

%start programa						// Es el axioma de la gramatica sintactica
%define parse.error detailed       // Mas detalles al encontrar un error 

%token 	FDT PROGRAMA DECLARAR LEER ESCRIBIR FIN_PROG IDENTIFICADOR CONSTANTE
%token ASIGNACION "<-"

%left  '-'  '+'       	// Tienen menor precedencia , va "mas arriba"
%left  '*'  '/'       	// Tienen mas precedencia
%precedence NEG			// Es el cambio de contexto del operador (ahora unario) '-'

%%
// Lo dejo con recursion a derecha la gramatica o la cambio a izquierda porque bison se lleva mejor ??? aaaaaaaaaaaaaaaaaaaaaaaaa
programa :					PROGRAMA listaSentencias FIN_PROG;

listaSentencias :			sentencia 
						| 	sentencia listaSentencias;

sentencia :					LEER'('listaIdentificadores')'';'			{printf("leer\n")} 
						|	ESCRIBIR'('listaExpresiones')'';'			{printf("escribir\n")} 
						|	DEFINIR IDENTIFICADOR';'					{printf("definir \n",)} 		// Falta el lexema del identificador de la declaracion
						|	IDENTIFICADOR"<-"expresion';'				{printf("asignación \n",)};

listaIdentificadores :		IDENTIFICADOR 
						| 	IDENTIFICADOR','listaIdentificadores;

listaExpresiones :			expresion 
						| 	expresion','listaExpresiones;
						
expresion:				  	valor
						| 	'-'valor %prec NEG							{printf("inversion\n");}
                        | 	'('expresion')' 							{printf("paréntesis\n");}
                        | 	expresion '+' expresion 					{printf("suma\n");}
                        | 	expresion '-' expresion 					{printf("resta\n");}
                        | 	expresion '*' expresion 					{printf("multiplicacion\n");}
                        | 	expresion '/' expresion 					{printf("division\n");};
                        
valor :						IDENTIFICADOR
						|	CONSTANTE
%%


// Informa la ocurrencia de un error en un determinada linea del fuente
void yyerror(const char *s){
		printf("línea #%d  %s\n", yylineno, s);
}
