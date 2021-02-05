#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 200


char* tablaDeSimbolos[MAX];
int proxPosicionDisponible = 0;

int existe(char* cadena){
	for (int i = 0; i < proxPosicionDisponible; i++){
		if (!strcmp(tablaDeSimbolos[i], cadena)) 			// si la cadena parametro no esta en la tabla
			return 1;	
	}	
	return 0;
}

void agregar(char* cadena){
	if(proxPosicionDisponible < MAX){
		tablaDeSimbolos[proxPosicionDisponible] = cadena;
		proxPosicionDisponible++;
	}
	else{
		printf("Se lleno la tabla de símbolos");
	}
}
