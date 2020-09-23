#include "scanner.h"

int estado_actual = 0;
char c;

int tabla_transicion[9][6] = 
{
    {1,   3,  5,  6,  0,  7},
    {1,   1,  2,  2,  2,  2},
    {99, 99, 99, 99, 99, 99},
    {4,   3,  4,  4,  4,  4},
    {99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99},
    {8,  8,  8,   8,  8,  7},
    {99, 99, 99, 99, 99, 99},
};

int cambiar_estado()
{
    if(isdigit(c))
        return tabla_transicion[estado_actual][DIGITO];
    else if(isalpha(c))
        return tabla_transicion[estado_actual][LETRA];
    else if(isspace(c))
        return tabla_transicion[estado_actual][ESPACIO];
    else if(c == '#')
        return tabla_transicion[estado_actual][NUMERAL];
    else if(c == EOF)
        return tabla_transicion[estado_actual][FDT];
    else    
        return tabla_transicion[estado_actual][OTRO];
}

// estado aceptor -> True
// estado no aceptor -> false
const bool estados[9] = {false,false,true,false,true,true,true,false,true};

bool debo_parar()
{
    return estados[estado_actual];
}

TOKEN token_reconocido()
{
    // podriamos usar un nuevo enum para los estados
    switch(estado_actual)
    {
    case 2: 
        ungetc(c,stdin); 
        return IDENTIFICADOR;
    case 4:
        ungetc(c,stdin); 
        return CONSTANTE_ENTERA;
    case 5:
        return NUMERAL;
    case 6:
        return FIN;
    case 8:
        ungetc(c,stdin); 
        return ERROR;
    }
}

TOKEN scanner()
{
    TOKEN tk;
    // hay que usar el estado_actual = 0 por aca y hacerlo local
    while(!debo_parar())
    {
        c = getchar();
        estado_actual = cambiar_estado();
    }
    tk = token_reconocido(); 
    estado_actual = 0;
    return tk;
}