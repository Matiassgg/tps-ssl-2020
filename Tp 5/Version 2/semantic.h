#ifndef SEMANTIC_H_INCLUDED
#define SEMANTIC_H_INCLUDED

int declarar(char*,int);
void comenzar(void);
void leer(char*);
void asignar(char*, char*);
void escribir(char*);
int verificarIdentificador(char*);
char* generarInfijo(char*,char,char*);
char* generarUnario(char*);
char* generarNuevoTemporal(void);
void finalizar(void);

#endif // SEMANTIC_H_INCLUDED
