#ifndef TUPLA_H
#define TUPLA_H

#include <stdlib.h>

typedef unsigned int u32;

typedef struct TuplaSt *Tupla;

// Crea una tupla a partir de 2 argumentos
Tupla crearTupla(u32 arg1, u32 arg2);

// Crea una nueva tupla con los argumentos rotados
Tupla rotarTupla(Tupla t);

// Retorna arg1 de t
u32 arg1Tupla(Tupla t);

// Retorna arg2 de t
u32 arg2Tupla(Tupla t);

// Modifica el argumento 1 de la tupla t
void modifArg1Tupla(Tupla t, u32 elem);

// Modifica el argumento 2 de la tupla t
void modifArg2Tupla(Tupla t, u32 elem);

// Funcion para pasar como argumento en 'qsort', ordena en forma ascendente
int compararTuplasAsc(const void *t1, const void *t2);

// Funcion para pasar como argumento en 'qsort', ordena en forma descendente segun arg2
int compararTuplasDesc(const void* t1, const void* t2);

// Libera la memoria
Tupla destruirTupla(Tupla t);

#endif
