#include <stdlib.h>
#include <stdio.h>

#include "APIG23.h"
#include "EstructuraGrafo23.h"
#include "tupla.h"

#define MAX_LINE_SIZE 1000

struct _GrafoSt {
    u32 cantidadVertices;
    u32 cantidadLados;
    u32 *nombres;
    u32 *grados;
    u32 delta;
    u32 **listaAdyacencia;
    u32 maxGrado;
};

static u32 busquedaBinaria(u32 *arr, u32 size, u32 valor) {
    u32 izq = 0;
    u32 der = size - 1;

    while (izq <= der) {
        u32 mitad = (izq + der) / 2;
        if (arr[mitad] == valor) {
            return mitad;
        } else if (arr[mitad] < valor) {
            izq = mitad + 1;
        } else {
            der = mitad - 1;
        }
    }

    return -1;
}

// CONSTRUCCION / DESTRUCCION
Grafo ConstruirGrafo() {

    u32 cantidadVertices = 0, cantidadLados = 0;
    u32 vert1, vert2;
    u32 indiceLado = 0, ladosLeidos = 0;
    char line[MAX_LINE_SIZE], edge[4];
    char p;
    Tupla *listaLados = NULL;
    while (fgets(line, MAX_LINE_SIZE, stdin) && ladosLeidos <= cantidadLados) {
        // salteamos todos los comentarios
        if (line[0] == 'c' || line[0] == '\n') {
            continue;

        // procesamos la cantidad de vertices y lados
        } else if (line[0] == 'p'){
            if (sscanf(line, "%c %s %u %u", &p, edge, &cantidadVertices, &cantidadLados) != 4)
                return NULL;
            if (cantidadVertices < 2 || cantidadLados == 0) 
                return NULL;
            // como ya se cuantos lados hay, creo la lista con 2*m lugares
            listaLados = calloc(2*cantidadLados, sizeof(Tupla));
    
        // procesamos los lados
        } else if (line[0]=='e') {
            if (sscanf(line, "%c %u %u", &p, &vert1, &vert2) != 3)
                return NULL;
            // cargar lados 
            listaLados[indiceLado] = crearTupla(vert1, vert2);
            listaLados[indiceLado+1] = crearTupla(vert2, vert1);
            indiceLado = indiceLado+2;
            ladosLeidos++;
        } else {
            return NULL;
        }
    }


    // Ordena la lista de lados, en base al primer elemento de la tupla
    qsort(listaLados, 2*cantidadLados, sizeof(Tupla), compararTuplasAsc);

    // Creacion del grafo
    Grafo grafo = malloc(sizeof(struct _GrafoSt));
    grafo->listaAdyacencia = calloc(cantidadVertices, sizeof(u32*));
    grafo->grados = calloc(cantidadVertices, sizeof(u32));
    grafo->nombres = calloc(cantidadVertices, sizeof(u32));
    grafo->cantidadLados = cantidadLados;
    grafo->cantidadVertices = cantidadVertices;
    grafo->delta = 0;


    u32 **vecinosNombres = calloc(cantidadVertices, sizeof(u32*));
    u32 verticeActual = arg1Tupla(listaLados[0]);
    u32 indiceVertice = 0;
    u32 indiceVecino = 0;
    grafo->nombres[0] = verticeActual;
    vecinosNombres[0] = calloc(1, sizeof(u32));

    // recorre listaLados (2m)
    for (u32 i = 0; i < 2*cantidadLados; i++) {
        
        if (verticeActual != arg1Tupla(listaLados[i])) {
            verticeActual = arg1Tupla(listaLados[i]);
            indiceVecino = 0;            
            indiceVertice++;
            vecinosNombres[indiceVertice] = calloc(1, sizeof(u32));
            grafo->nombres[indiceVertice] = verticeActual;
        }

        grafo->grados[indiceVertice]++;
        vecinosNombres[indiceVertice] = realloc(vecinosNombres[indiceVertice], grafo->grados[indiceVertice]*sizeof(u32));
        vecinosNombres[indiceVertice][indiceVecino] = arg2Tupla(listaLados[i]);
        indiceVecino++;
        destruirTupla(listaLados[i]);
    }
    
    // vecinosNombre
    for (unsigned int i = 0; i < cantidadVertices; i++) {
        grafo->listaAdyacencia[i] = calloc(grafo->grados[i], sizeof(u32));
        for (unsigned int j = 0; j < grafo->grados[i]; j++) {
            grafo->listaAdyacencia[i][j] = busquedaBinaria(grafo->nombres, cantidadVertices, vecinosNombres[i][j]);
        }
        free(vecinosNombres[i]);
        vecinosNombres[i] = NULL;
        u32 grado = Grado(i, grafo);
        if (grado > Delta(grafo))
            grafo->delta = grado;
    }

    free(vecinosNombres);
    vecinosNombres = NULL;
    free(listaLados);
    listaLados = NULL;
    
    return grafo;
}   


void DestruirGrafo(Grafo G){
    free(G->nombres);
    G->nombres = NULL;
    free(G->grados);
    G->grados = NULL;
    for (u32 i = 0; i < G->cantidadVertices; i++) {
        free(G->listaAdyacencia[i]);
        G->listaAdyacencia[i] = NULL;
    }
    free(G->listaAdyacencia);
    G->listaAdyacencia = NULL;
    free(G);
    G=NULL;
}


u32 NumeroDeVertices(Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);
    return G->cantidadVertices;
}


u32 NumeroDeLados(Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);
    return G->cantidadLados;
}


u32 Delta(Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);
    return G->delta;
}


u32 Nombre(u32 i, Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);
    return G->nombres[i];
}


u32 Grado(u32 i, Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);
    if (i >= NumeroDeVertices(G))
        return -1;
    return G->grados[i];
}


u32 IndiceVecino(u32 j, u32 i, Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);

    if (i > NumeroDeVertices(G) && j > NumeroDeVertices(G))
        exit(EXIT_FAILURE);

    if (i >= NumeroDeVertices(G) || (i < NumeroDeVertices(G) && j >= Grado(i, G)))
        return -1;

    return G->listaAdyacencia[i][j];
}
