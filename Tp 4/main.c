//////////////////////////////////////////////////////////////////////////////////////
/*
      TP3-2020-"Parser del lenguaje mini con Bison"
      Grupo 03
*/                                                             
//////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
//#include "parser.h"
//#include "scanner.h"

int main(void)
{	
	switch(yyparse()){
		case 0:
			printf("Exito"); printf("Errores sintacticos: X - Errores lexicos: X");	// faltan las variables
			return 0;
		case 1:
			printf("Error"); printf("Errores sintacticos: X - Errores lexicos: X");	// faltan las variables
			return 1;
		case 2:
			printf("Memoria insuficiente");
			return 2;
	}
	return 0;		
}
