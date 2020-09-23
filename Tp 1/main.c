#include "scanner.h"    // incluyo el .h , y no el .c
#include <stdlib.h>     // solo la uso aca esta libreria , entonces no va estrictamente en el .h

int identificadores = 0;
int constantes = 0;
int numerales = 0; 
int errores = 0;

int main(void)
{
    TOKEN token_leido;
    printf("-------------------\n");
    do
    {  
        token_leido = scanner();              
        switch(token_leido)
        {
            case IDENTIFICADOR:
            printf("Identificador\n");
            identificadores++;    
            break;
            case CONSTANTE_ENTERA:
            printf("Constante entera\n");
            constantes++;
            break;
            case NUMERAL:
            printf("Numeral\n");
            numerales++;
            break;
            case ERROR:
            printf("Error\n");
            errores++;
            break;
            }
    } while(token_leido != FIN);

    printf("-------------------\n");
    printf("Totales:\n");
    printf("Identificadores: %i\n",identificadores);
    printf("Constantes enteras: %i\n",constantes);
    printf("Numerales: %i\n",numerales);
    printf("Errores: %i\n",errores);

    return EXIT_SUCCESS;
}