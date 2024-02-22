#ifndef __APIP2_H
#define __APIP2_H


#include "APIG23.h" 

#include "ColoreoGrafo.h"

#include "ArrayUtils.h"


#define NULL_COLOR UINT32_MAX
#define MAX_U32 UINT32_MAX

//se asume que Orden y Color tienen alocadas las cantidades correctas de memoria

/*corre Greedy en el orden dado por Orden, cargando el coloreo en Color y devolviendo el numero de colores usado */
u32 Greedy(Grafo G,u32* Orden,u32* Color, u32 k, u32 n);

u32 GreedyDinamico(Grafo G, u32* Orden, u32* Color, u32 p);

char FirstOrder(Grafo G, u32 *Orden, u32 *Color);

char SecondOrder(Grafo G, u32 *Orden,u32 *Color);

#endif
