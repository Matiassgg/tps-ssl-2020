#ifndef SEMANTIC_H_INCLUDED
#define SEMANTIC_H_INCLUDED

void Comenzar (void);
void Terminar (void);
void Asignar (char *izquierda, char *derecha);
void Leer (char *in);
void Escribir (char *out);
int ProcesarId (char *identificador);
char *GenInfijo (char *e1, char op, char *e2);
char *GenUnario (char op, char *e);
void Generar (char *OP, char *A, char *B, char *C);


#endif // SEMANTIC_H_INCLUDED
