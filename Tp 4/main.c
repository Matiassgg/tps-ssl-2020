//////////////////////////////////////////////////////////////////////////////////////
/*
      TP4-2020-"Parser del lenguaje mini con Bison"
      Grupo 03
*/                                                             
//////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "parser.h"
#include "scanner.h"
extern int yynerrs;

int main(void)
{	
	switch(yyparse()){
		case 0:
			printf("Exito"); printf("Errores sintacticos: %d - Errores lexicos: %d\n",yynerrs,errlex);	
			return 0;
		case 1:
			printf("Error"); printf("Errores sintacticos: %d - Errores lexicos: %d\n",yynerrs,errlex);	
			return 1;
		case 2:
			printf("Memoria insuficiente");
			return 2;
	}
	return 0;		
}
