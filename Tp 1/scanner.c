#include "scanner.h"

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

TOKEN scanner(FILE* archivo)
{
    TOKEN tk;
    // aca se recorre el archivo haciendo fgetc() y ungetc() eventualmente
    return tk;
}