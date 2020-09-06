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

#endif // SCANNER_H_INCLUDED