#include <stdio.h>
#include <stdlib.h>     // para EXIT_SUCESS , EXIT_FAILURE , etc
#include <ctype.h>      // para las funciones isalpha(...) , isspace(...) , etc

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
