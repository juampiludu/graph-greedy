#ifndef APIG23_H
#define APIG23_H


#include <stdlib.h>
#include <stdio.h>


//el .h de abajo debe tener definida GrafoSt y u32.
#include "EstructuraGrafo23.h"



//Grafo es un puntero a una estructura GrafoSt, la cual debe estar definida en el .h de arriba
typedef GrafoSt *Grafo;


// CONSTRUCCION / DESTRUCCION

// Crea un grafo, leyendo desde stdin
Grafo ConstruirGrafo();

// Destruye el grafo
void DestruirGrafo(Grafo G);

// INFORMACION DEL GRAFO

// Devuelve el numero de vertices de G.
u32 NumeroDeVertices(Grafo G);

// Devuelve el numero de lados de G.
u32 NumeroDeLados(Grafo G);

// Devuelve el mayor grado de G.
u32 Delta(Grafo G);


// INFORMACION DE LOS VERTICES

// Devuelve el nombre del vertice cuyo indice es i en el Orden Natural. 
// (como figuraba en el input)
u32 Nombre(u32 i, Grafo G);

// Devuelve el grado del vertice cuyo indice es i en el Orden Natural. 
u32 Grado(u32 i, Grafo G);

// Devuelve el indice en el Orden Natural de un vecino del vertice i 
u32 IndiceVecino(u32 j, u32 i, Grafo G);


#endif