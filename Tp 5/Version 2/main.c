//////////////////////////////////////////////////////////////////////////////////////
/*
      TP5-2020-"Front end de compilador del lenguaje mini"
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
	switch(yyparse()){
		case 0:
			printf("Compilación terminada con éxito\n");
			break;
		case 1:
			printf("Errores de compilación\n"); 
			break;
		case 2:
			printf("Memoria insuficiente\n");
			break;
	}
	printf("Errores sintácticos: %d - Errores léxicos: %d - Errores semánticos: %d\n",yynerrs,errlex,errsemtc);
	return 0;
}
