//////////////////////////////////////////////////////////////////////////////////////
/*
      TP3 2018 "Flex"
      Grupo 03
      
      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/                                                             
//////////////////////////////////////////////////////////////////////////////////////

<<<<<<< HEAD
=======
// Esta cabecera la generas despues de haber hecho "flex scanner.l"
>>>>>>> d579bb5f15bed1c46d3c5ab3104ab816fb69b296
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
