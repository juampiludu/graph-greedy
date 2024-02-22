#include <stdio.h>
#include <stdlib.h>
#include "APIParte2.h"

// estructura para que sea mas facil hacer el cambio
struct CuatroUpla{
    u32* color;
    u32* orden;
    u32 actualCantidadColores;
    u32 prevCantidadColores;
};

int main() {
    Grafo G = ConstruirGrafo();
    if (G == NULL) {
        printf("Error creando grafo \n");
    }
    
    u32 N = NumeroDeVertices(G);

    
    struct CuatroUpla t1;
    t1.color = calloc(N, sizeof(u32));
    t1.orden = calloc(N, sizeof(u32));
    t1.actualCantidadColores = 0;
    
    struct CuatroUpla t2;
    t2.color = calloc(N, sizeof(u32));
    t2.orden = calloc(N, sizeof(u32));
    t2.actualCantidadColores = 0;

    // Orden natural
    for (u32 i = 0; i < N; i++) {
        t1.orden[i] = i;
        t2.orden[i] = i;
    }
    

    t1.prevCantidadColores = Greedy(G, t1.orden, t1.color);
    t2.prevCantidadColores = Greedy(G, t2.orden ,t2.color);

    u32 ji_x = -1;

    
    for (u32 i = 0; i < 500; i++) {
        printf("i:%u\n",i);

        // Cada 16 cambiamos
        if (i!=0 && i%16==0) {
            struct CuatroUpla t_tmp = t1;
            t1 = t2;
            t2 = t_tmp;
        }

        // Ordenamos
        if (OrdenImparPar(N, t1.orden, t1.color) == '1' || OrdenJedi(G, t2.orden, t2.color) == '1') {
            printf("Error de ordenamiento \n");
            printf("Error de ordenamiento \n");
            exit(1);
        }        

        // Corremos greedy
        t1.actualCantidadColores = Greedy(G, t1.orden, t1.color);
        t2.actualCantidadColores = Greedy(G, t2.orden, t2.color);
        
        // Nos aseguramos que se cumple el teorema
        if (t1.actualCantidadColores > t1.prevCantidadColores || t2.actualCantidadColores > t2.prevCantidadColores) {
            printf("No se cumple teorema\n");
            exit(1);   
        }

        // Actualizamos la estructura
        t1.prevCantidadColores = t1.actualCantidadColores;
        t2.prevCantidadColores = t2.actualCantidadColores;


        // Actualizamos ji_x
        ji_x =  t2.actualCantidadColores;
        if (t2.actualCantidadColores < ji_x) {
            ji_x = t2.actualCantidadColores;
        }
    }

    // Liberamos memoria
    free(t1.color);
    free(t1.orden);
    free(t2.color);
    free(t2.orden);
    DestruirGrafo(G);
    
    // Mostramos resultado de la aproximacion
    printf("JI=%u\n\n",ji_x);
    return 0;

}