//////////////////////////////////////////////////////////////////////////////////////
/*
      TP3-2020-"Flex"
      Grupo 03
      
      Matias Gabriel Grillo - 16-7053-0
      Julieta Bertachi      - 16-4393-9
      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/                                                             
//////////////////////////////////////////////////////////////////////////////////////

#include "scanner.h"
int TOKEN;
char *token_names[] = {"Fin de archivo","Programa","Declarar","Leer","Escribir","Fin-Prog","Asignacion","Identificador","Constante"};

int main()
{
	do
	{
		TOKEN = yylex();
		if(TOKEN <= ASIGNACION){
			// Muestro el TOKEN correspondiente a la gramatica
			printf("Token: %s\n",token_names[TOKEN]);
		}
		else if(TOKEN == IDENTIFICADOR || TOKEN == CONSTANTE){
			// Ademas del TOKEN , aca muestro el lexema que corresponde
			printf("Token: %s\tlexema: %s\n",token_names[TOKEN],yytext);
		}
		else{
			// Si es solo un caracter el TOKEN, muestro ese caracter
			printf("Token: \'%c\'\n",TOKEN);
		}		 
	} while(TOKEN != FDT);
        
	return EXIT_SUCCESS;		
}
