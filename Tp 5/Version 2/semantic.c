#include <stdio.h>
#include <string.h>
#include "symbol.h"
#include "parser.h"
#include "semantic.h"

int errsemtc = 0;
char buffer2[200];
char temporal[30];
int nro_temporal = 1;

int declarar(char* identificador, int bytes){
	if(existe(identificador)){
		sprintf(buffer2,"Error semántico: identificador %s ya declarado", identificador);
		errsemtc++;
		yyerror(buffer2);
		return 1;
	}
	else{
		agregar(identificador);
		printf("Reserve %s,%d\n", identificador,bytes);	
		return 0;		
	}

}

void comenzar(void){
	printf("Load rtlib,\n");
}

void leer(char* identificador){
	printf("Read %s,Integer\n", identificador);
}

void asignar(char* resultado, char* identificador) {
	printf("Store %s,%s \n", resultado, identificador);
}

void escribir(char* identificador){
	printf("Write %s,Integer\n", identificador);
}

int verificarIdentificador(char* identificador){
	if(!existe(identificador)){
		sprintf(buffer2,"Error semántico: identificador %s no declarado", identificador);
		errsemtc++;
		yyerror(buffer2);
		return 1;
	}
	return 0;
}

char* generarInfijo(char* entradaA, char operador, char* entradaB){
	char* nuevoTemporal = generarNuevoTemporal();
	declarar(nuevoTemporal,4);
	switch(operador){
		case '+':
			printf("ADD %s,%s,%s\n", entradaA, entradaB, nuevoTemporal);
			break;
		case '*':
			printf("MUL %s,%s,%s\n", entradaA, entradaB, nuevoTemporal);
			break;
		case '-':
			printf("SUB %s,%s,%s\n", entradaA, entradaB, nuevoTemporal);
			break;
		case '/':
			printf("DIV %s,%s,%s\n", entradaA, entradaB, nuevoTemporal);
			break;
	}
	return nuevoTemporal;
}

char* generarUnario(char* entrada){
  	char* nuevoTemporal = generarNuevoTemporal();
  	declarar(nuevoTemporal,4);
	printf("NEG %s,%s,%s\n", entrada, "", nuevoTemporal);
	return nuevoTemporal;
}

char* generarNuevoTemporal(void){
  	sprintf(temporal,"Temp#%d",nro_temporal);
  	nro_temporal++;
  	return strdup(temporal);	
}

void finalizar(void){
	printf("Exit,\n");
}

