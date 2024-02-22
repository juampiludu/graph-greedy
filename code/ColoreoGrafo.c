#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "APIParte3.h"
#include "ColoreoGrafo.h"
#include "ArrayUtils.h"

struct s_FirstOrder {
    u32 grado;
    u32 color;
    u32 suma;
};


struct s_GreedyDinamico {
    u32 valor;
    u32 indice;
};


int cmpGradoAsc(const void *a, const void *b) {
    const struct s_FirstOrder *elem1 = (const struct s_FirstOrder *)a;
    const struct s_FirstOrder *elem2 = (const struct s_FirstOrder *)b;

    if (elem1->grado < elem2->grado) {
        return -1;
    }
    else if (elem1->grado > elem2->grado) {
        return 1;
    }
    else {
        return 0;
    }
}


int cmpGradoDesc(const void *a, const void *b) {
    const struct s_FirstOrder *elem1 = (const struct s_FirstOrder *)a;
    const struct s_FirstOrder *elem2 = (const struct s_FirstOrder *)b;

    if (elem1->grado > elem2->grado) {
        return -1;
    }
    else if (elem1->grado < elem2->grado) {
        return 1;
    }
    else {
        return 0;
    }
}


u32 *LISTA_E;
u32 *LISTA_S;
u32 *LISTA_COLOR;


int cmpFirstOrden(const void *a, const void *b) {
    const u32 index_a = *(const u32*)a;
    const u32 index_b = *(const u32*)b;
    // u32 colorA = LISTA_COLOR[index_a];
    // u32 colorB = LISTA_COLOR[index_b];
    u32 valorE1 = LISTA_E[index_a];
    u32 valorE2 = LISTA_E[index_b];

    if (valorE1 > valorE2) {
        return -1;
    }
    else if (valorE1 < valorE2) {
        return 1;
    }
    else {
        return 0;
    }
}


int cmpSecondOrder(const void *a, const void *b) {
    const u32 index_a = *(const u32*)a;
    const u32 index_b = *(const u32*)b;
    u32 colorA = LISTA_COLOR[index_a];
    u32 colorB = LISTA_COLOR[index_b];
    u32 valorS1 = LISTA_S[colorA];
    u32 valorS2 = LISTA_S[colorB];

    if (valorS1 > valorS2) {
        return -1;
    }
    else if (valorS1 < valorS2) {
        return 1;
    }
    else {
        return 0;
    }
}


int cmpGreedyDinamico(const void *a, const void *b) {
    const struct s_GreedyDinamico *elem1 = (const struct s_GreedyDinamico *)a;
    const struct s_GreedyDinamico *elem2 = (const struct s_GreedyDinamico *)b;

    u32 valor1 = elem1->valor;
    u32 valor2 = elem2->valor;

    if (valor1 < valor2) {
        return 1;
    }
    else if (valor1 > valor2) {
        return -1;
    }
    else {
        if (elem1->indice < elem2->indice) {
            return -1;
        }
        else if (elem1->indice > elem2->indice) {
            return 1;
        }
        else {
            return 0;
        }
    }
}


u32 Greedy(Grafo G, u32* Orden, u32* Color, u32 k, u32 n) {
    u32 maxColor = 0;
    
    u32 indiceVertice = Orden[0];
    
    Color[indiceVertice] = 0;

    for (u32 i = k; i < n; i++) {
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


u32 GreedyDinamico(Grafo G, u32* Orden, u32* Color, u32 p) {
    u32 n = NumeroDeVertices(G);
    
    if (p >= n) {
        return Greedy(G, Orden, Color, 0, n);
    }

    u32 maxColor = Greedy(G, Orden, Color, 0, p);
    u32 np = n - p;

    struct s_GreedyDinamico *listaGrDin = malloc(np * sizeof(struct s_GreedyDinamico));

    for (u32 i = p; i < n; i++) {
        u32 indiceVertice = Orden[i];
        u32 gradoVertice = Grado(indiceVertice, G);
        u32 nc = 0;

        u32 *coloresUsados = calloc(gradoVertice, sizeof(u32));

        for (u32 j = 0; j < gradoVertice; j++) {
            u32 indiceVecino = IndiceVecino(j, indiceVertice, G);
            u32 colorVecino = Color[indiceVecino];

            coloresUsados[j] = colorVecino;
        }
        
        qsort(coloresUsados, gradoVertice, sizeof(u32), cmpAsc);
        
        for (u32 j = 1; j < gradoVertice; j++) {
            if (coloresUsados[j-1] != coloresUsados[j])
                nc++;
        }

        listaGrDin[i-p].valor = nc;
        listaGrDin[i-p].indice = indiceVertice;

        free(coloresUsados);
        coloresUsados = NULL;
    }

    qsort(listaGrDin, np, sizeof(struct s_GreedyDinamico), cmpGreedyDinamico);

    for (u32 i = p; i < n; i++) {
        Orden[i] = listaGrDin[i-p].indice;
    }

    free(listaGrDin);
    listaGrDin = NULL;

    maxColor = max(maxColor, Greedy(G, Orden, Color, p, n));

    return maxColor;
}


struct s_FirstOrder *initFO(u32 n, bool esMin) {
    struct s_FirstOrder *fo = malloc(n * sizeof(struct s_FirstOrder));
    
    for (u32 i = 0; i < n; i++) {
        fo[i].color = 0;
        fo[i].grado = esMin ? MAX_U32 : 0;
    }

    return fo;
}


struct s_FirstOrder *minimosGrados(Grafo G, u32 *Color, u32 *Orden, u32 n) {
    struct s_FirstOrder *ocurrencias = initFO(n, true);

    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        u32 color = Color[vertice];
        ocurrencias[color].grado = Grado(vertice, G);
        ocurrencias[color].color = color;
    }

    qsort(ocurrencias, n, sizeof(struct s_FirstOrder), cmpGradoAsc);

    return ocurrencias;
}


struct s_FirstOrder *maximosGrados(Grafo G, u32 *Color, u32 *Orden, u32 n) {
    struct s_FirstOrder *ocurrencias = initFO(n, false);

    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        u32 color = Color[vertice];
        ocurrencias[color].grado = Grado(vertice, G);
        ocurrencias[color].color = color;
    }

    qsort(ocurrencias, n, sizeof(struct s_FirstOrder), cmpGradoDesc);

    return ocurrencias;
}


u32 getGradoFrom(u32 x, u32 n, struct s_FirstOrder *lista) {
    u32 res;

    for (u32 i = 0; i < n; i++) {
        if (lista[i].color == x) {
            res = lista[i].grado;
            break;
        }
    }

    return res;
}


char FirstOrder(Grafo G, u32 *Orden, u32 *Color) {
    printf("\nFirst Order\n\n");
    u32 n = NumeroDeVertices(G);
    
    struct s_FirstOrder *m = minimosGrados(G, Color, Orden, n);
    struct s_FirstOrder *M = maximosGrados(G, Color, Orden, n);

    u32 *listaE = malloc(n * sizeof(struct s_FirstOrder));

    for (u32 i = 0; i < n; i++) {
        u32 color = Color[i];
        u32 elemE, minGrado, maxGrado;

        if ((color + 2) % 3 == 0) {
            minGrado = getGradoFrom(color, n, m);
            elemE = 0x7fffffff + minGrado;
        }
        else if ((color + 1) % 3 == 0) {
            maxGrado = getGradoFrom(color, n, M);
            elemE = 0x1fff + maxGrado;
        }
        else if (color % 3 == 0) {
            minGrado = getGradoFrom(color, n, m);
            maxGrado = getGradoFrom(color, n, M);
            elemE = minGrado + maxGrado;
        }

        listaE[i] = elemE;
    }

    LISTA_E = listaE;
    LISTA_COLOR = Color;
    
    qsort(Orden, n, sizeof(u32), cmpFirstOrden);

    free(listaE);
    listaE = NULL;
    free(m);
    m = NULL;
    free(M);
    M = NULL;
    
    return '0';
}


void S(u32 *listaS, u32 n, Grafo G, u32 *Color, u32 *Orden) {
    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        u32 color = Color[vertice];
        u32 grado = Grado(vertice, G);
        
        if (grado > 1) {
            listaS[color] += grado;
        }
    }
}


char SecondOrder(Grafo G, u32 *Orden,u32 *Color) {
    printf("\nSecond Order\n\n");
    u32 n = NumeroDeVertices(G);

    u32 *listaS = calloc(n, sizeof(u32));

    S(listaS, n, G, Color, Orden);

    LISTA_S = listaS;
    LISTA_COLOR = Color;

    qsort(Orden, n, sizeof(u32), cmpSecondOrder);

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