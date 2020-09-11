#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>      
#include <stdbool.h>    

typedef enum
{
    IDENTIFICADOR, 
    CONSTANTE_ENTERA, 
    NUMERAL,
    ERROR,
    FIN
} TOKEN;    // Tokens que reconozco

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
TOKEN scanner();
int cambiar_estado();
TOKEN token_reconocido();
bool debo_parar();

#endif // SCANNER_H_INCLUDED