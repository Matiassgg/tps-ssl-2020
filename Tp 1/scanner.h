#include <stdio.h>
#include <stdlib.h>     // para EXIT_SUCESS , EXIT_FAILURE , etc
#include <ctype.h>      // para las funciones isalpha(...) , isspace(...) , etc
#include <stdbool.h>    // para poder usar el tipo 'bool'

typedef enum
{
    IDENTIFICADOR, 
    CONSTANTE_ENTERA, 
    NUMERAL,
    ERROR,
    FIN
} TOKEN;    // Lexemas

typedef enum
{
    LETRA,
    DIGITO,
    NUM,
    FDT,
    ESPACIO,
    OTRO
} CARACTER;     // Columnas de la TT


// Declaraciones de funciones a utilizar
TOKEN scanner(FILE*);
int cambiar_estado(CARACTER);
TOKEN token_reconocido(int,FILE*);
bool debo_parar(int);
