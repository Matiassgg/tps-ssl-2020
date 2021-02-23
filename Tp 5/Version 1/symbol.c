#include <stdio.h>
#include "scanner.h"
#include "parser.h"
#include "semantic.h"
#include "symbol.h"

#define max 200

char *TDS[max];
int ultimo = 0;

int Buscar (char * cadena) {        // si lo encuentra retorna 1
    for (int i=0 ; i < ultimo ; i++) {
        if (!strcmp(TDS[i],cadena)) { // if(cadena == TDS[i]) {
            return 1;
        }
    }
    return 0;
}

void Colocar (char *cadena) {
    if (ultimo < max) {
        TDS[ultimo]= cadena;
        ultimo++;
    } else
    printf("\n Se llenó la tabla de símbolos");
}


int Chequear (char *s) {
    
    char msg2[120];
    
        if (! Buscar(s)) {      /* ¿la cadena está en la Tabla de Símbolos? No: */
        Colocar (s);        /* almacenarla, es el nombre de una variable */
        Generar ("Reserve", s, "4", "");   /* genera la instrucción */
        return 1;
    } else {
        errSemanticos++;
        sprintf(msg2, "Error semántico: identificador %s ya declarado", s);
        yyerror(msg2);
        return 0; // error redeclaración
    }
}








