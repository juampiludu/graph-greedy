#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "APIParte2.h"
#include "ColoreoGrafo.h"
#include "ArrayUtils.h"

u32 *LISTA_COLOR;
u32 *LISTA_F;

u32 Greedy(Grafo G, u32* Orden, u32* Color) {
    u32 n = NumeroDeVertices(G);
    u32 maxColor = 0;
    
    u32 indiceVertice = Orden[0];
    
    Color[indiceVertice] = 0;

    for (u32 i = 0; i < n; i++) {
        indiceVertice = Orden[i];
        
        u32 colorVertice = 0;
        u32 gradoVertice = Grado(indiceVertice, G);
        u32 *coloresUsados = malloc(gradoVertice * sizeof(u32));

        for (u32 j = 0; j < gradoVertice; j++) {
            u32 indiceVecino = IndiceVecino(j, indiceVertice, G);
            u32 colorVecino = Color[indiceVecino];

            coloresUsados[j] = colorVecino;
        }

        qsort(coloresUsados, gradoVertice, sizeof(u32), cmpAsc);

        for (u32 j = 0; j < gradoVertice; j++) {
            if (coloresUsados[j] == colorVertice)
                colorVertice++;
        }

        Color[indiceVertice] = colorVertice;

        maxColor = max(maxColor, colorVertice);

        free(coloresUsados);
        coloresUsados = NULL;
    }

    return maxColor + 1;
}

// Primero los impares luego los pares.
int cmpImparPar(const void* v1, const void* v2) { 
    u32 colorV1 = LISTA_COLOR[*(u32 *)v1];  // 4
    u32 colorV2 = LISTA_COLOR[*(u32 *)v2];  // 7
    
    bool colorV1_impar = (colorV1 % 2) == 1;
    bool colorV2_impar = (colorV2 % 2) == 1;
    
    // Si tienen la misma paridad ordenamos por valor
    if(colorV1_impar == colorV2_impar) 
        return colorV1 - colorV2;

    // Si v1 es impar y v2 es par
    if (colorV1_impar && !colorV2_impar) 
        return -1;

    // Si v1 es par y v2 es impar
        return 1;
}

char OrdenImparPar(u32 n, u32* Orden, u32* Color) {
    // Seteamos variables gloables para poder comparar
    LISTA_COLOR = Color;
    qsort(Orden, n, sizeof(u32), cmpImparPar);

    return '0';
}


// JEDI
// ver enunciado
int cmpJedi(const void *v1, const void *v2) {
    u32 colorV1 = LISTA_COLOR[*(u32 *)v1];
    u32 colorV2 = LISTA_COLOR[*(u32 *)v2];
    u32 valorFV1 = LISTA_F[colorV1];
    u32 valorFV2 = LISTA_F[colorV2];

    // Si F(x) = F(y) ponemos todos los vertices del mismo color juntos 
    // (hacemos un bloque con el mismo color)
    if (valorFV1 == valorFV2)
        return colorV2 - colorV1;
    else {
        // sino usamos orden invertido (ie, queda como menor el que es numericamente mayor)
        return valorFV2 - valorFV1;
    }
}


void F(u32 *listaF, u32 n, Grafo G, u32 *Color, u32 *maxColor) {
    // Calculamos f(x) parcial para cada uno 
    // y calculamos la cantidad de colores
    for (u32 i = 0; i < n; i++) {
        listaF[Color[i]] += Grado(i, G) * Color[i];
        *maxColor = *maxColor > Color[i] ? *maxColor : Color[i];
    }
}


char OrdenJedi(Grafo G, u32* Orden, u32* Color) {
    u32 n = NumeroDeVertices(G);
    u32 maxColor = 0;

    // Cota superior de cantidad de colores por teorema
    u32 *listaF = calloc(Delta(G)+1, sizeof(u32));

    if (listaF == NULL) return '1';

    F(listaF, n, G, Color, &maxColor);
    // Aca ya tenemos F(x) calculado para cada color

    // Como sabemos la cantidad de colores, recortamos el array
    listaF = realloc(listaF, (maxColor+1) * sizeof(u32));

    // Seteamos variables globales para poder comparar
    LISTA_COLOR = Color;
    LISTA_F = listaF;
    qsort(Orden, n, sizeof(u32), cmpJedi);

    free(listaF);
    listaF = NULL;

    return '0';
}

char OrdenNatural(u32 n, u32 *Orden) {
    printf("\nOrden Natural\n\n");
    for (u32 i = 0; i < n; i++) {
        Orden[i] = i;
    }

    return '0';
}


char OrdenDescendente(u32 n, u32 *Orden) {
    printf("\nOrden Descendente\n\n");
    for (u32 i = 0; i < n; i++) {
        Orden[i] = n - i - 1;
    }

    return '0';
}