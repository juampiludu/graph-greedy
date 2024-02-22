#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "APIParte3.h"


void InfoGrafo(Grafo G) {
    printf("\n///// Informacion del Grafo /////\n\n");
    printf(" - Numero de vertices: %u\n", NumeroDeVertices(G));
    printf(" - Numero de lados:    %u\n", NumeroDeLados(G));
    printf(" - Delta:              %u\n", Delta(G));
    printf("\n/////////////////////////////////\n");
}


int main() {
    Grafo grafo = ConstruirGrafo();
    u32 n = NumeroDeVertices(grafo);
    u32 *Orden, *Color;
    u32 max_color;

    InfoGrafo(grafo);

    Orden = malloc(n * sizeof(u32));
    Color = malloc(n * sizeof(u32));
    memset(Color, NULL_COLOR, n * sizeof(u32));

    u32 p = 2;
    printf("p seleccionado: %u\n", p);
    

    OrdenNatural(n, Orden);

    max_color = GreedyDinamico(grafo, Orden, Color, p);
    printf("\nχ(G) = %u\n", max_color);
    printf("\n\n");
    
    SecondOrder(grafo, Orden, Color);

    max_color = GreedyDinamico(grafo, Orden, Color, p);    
    printf("\nχ(G) = %u\n", max_color);
    printf("\n\n");

    free(Orden);
    Orden = NULL;
    free(Color);
    Color = NULL;
    
    DestruirGrafo(grafo);
    return 0;
}
