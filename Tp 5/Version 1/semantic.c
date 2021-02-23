#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "parser.h"
#include "semantic.h"
#include "symbol.h"

int numeroTemp = 1;
int errSemanticos = 0;

void Comenzar (void) { /* inicializaciones semánticas */
    Generar("Load", "rtlib", "", "");
}

void Terminar (void) {
/* genera la instrucción para terminar la ejecución del programa */
    Generar ("Exit", "", "", "");
}

void Asignar (char *izquierda, char *derecha) {
/* genera la instrucción para la asignación */
    Generar("Store", derecha, izquierda, "");
}

void Leer (char *in) {
    /* genera la instrucción para leer */
    Generar("Read", in, "Integer", "");
}

// void ProcesarCte(void) {
//     /* convierte cadena que representa número a número entero y construye un registro semántico */
//     REG_EXPRESION t;
//     t.clase = CONSTANTE;
//     sscanf (buffer, "%d", &t.valor);
//     return t;
// }

void Escribir (char *out) {
    Generar("Write", out, "Integer", "");
}

int ProcesarId (char *identificador) {
    /* Declarar ID y construye el correspondiente registro semántico */
     char msg3[120];

    if (! Buscar(identificador)) {
        errSemanticos++;
        sprintf(msg3, "Error semántico: identificador %s NO declarado", identificador);
        yyerror(msg3);
        return 1;
    }
    return 0;
}

char *GenInfijo (char *e1, char op, char *e2) {
    /* Genera la instrucción para una operación infija y construye un registro semántico con el resultado */
    char variableNueva[9];
    char *cadenaNueva;

    sprintf(variableNueva,"Temp#%d", numeroTemp);
    cadenaNueva = strdup(variableNueva);
    Chequear(cadenaNueva);
    numeroTemp++;
    
    switch(op) {
        case '+':   Generar("ADD", e1, e2, cadenaNueva);
                    break;
        case '-':   Generar("SUB", e1, e2, cadenaNueva);
                    break;
        case '*':   Generar("MUL", e1, e2, cadenaNueva);
                    break;
        case '/':   Generar("DIV", e1, e2, cadenaNueva);
    }

    return cadenaNueva;
}

char *GenUnario (char op, char *e) {
    /* Genera la instrucción para una operación infija y construye un registro semántico con el resultado */
    char variableNueva[9];
    char *cadenaNueva;

    sprintf(variableNueva,"Temp#%d", numeroTemp);
    cadenaNueva = strdup(variableNueva);
    Chequear(cadenaNueva);
    numeroTemp++;
    if(op == '-')
        Generar("NEG", e, "", cadenaNueva);
    return cadenaNueva;

}

void Generar (char *OP, char *A, char *B, char *C) {
    if (!strcmp(C, "")) {              //if (C == "") {
        printf("\n%s %s,%s", OP, A, B);
    } else if (!strcmp(B, "")) {           //} else if (B == "") {
        printf("\n%s %s,,%s", OP, A, C);
    } else {
        printf("\n%s %s,%s,%s", OP, A, B, C);
    }
}

// Extraer() {

// }
