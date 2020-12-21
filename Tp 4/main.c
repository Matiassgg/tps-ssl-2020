//////////////////////////////////////////////////////////////////////////////////////
/*
      TP4-2020-"Parser del lenguaje mini con Bison"
      Grupo 03

      Matias Gabriel Grillo - 16-7053-0
      Julieta Bertachi      - 16-4393-9
      Leonardo M. Hanashiro - 16-3876-2
*/                                                             
//////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "parser.h"

int main(void)
{	
	switch( yyparse() ) {
		case 0: printf("\nCompilación terminada con éxito");
			break;		
		case 1: printf("\nErrores de compilación");
			break;
		case 2: printf("\nNo hay memoria suficiente");
			break;		
		}
	printf("\nErrores sintácticos:  %d - Errores lexicos:  %d\n", yynerrs, errlex);

	return 0;		
}
