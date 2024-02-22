#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "APIParte2.h"

#include "ColoreoGrafo.h"


void printArray(u32 *arr, u32 len) {
    printf("[");
    for (u32 i = 0; i < len; i++) {
        printf("%u", arr[i]);
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


void printNombres(Grafo G) {
    u32 len = NumeroDeVertices(G);
    printf("[");
    for (u32 i = 0; i < len; i++) {
        printf("%u", Nombre(i, G));
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


void printTuplaArg(Tupla *arr, u32 len, u32 (*fun)(Tupla)) {
    printf("[");
    for (u32 i = 0; i < len; i++) {
        printf("%u", fun(arr[i]));
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


void mergeArrays(u32 *arr1, u32 len1, u32 *arr2, u32 len2, u32 *target) {
    memcpy(target       , arr1, len1 * sizeof(u32));
    memcpy(target + len1, arr2, len2 * sizeof(u32));
}

u32 *copyArray(u32 *src, u32 len) {
    u32 *new_array = malloc(len * sizeof(u32));
    memcpy(new_array, src, len * sizeof(u32));
    return new_array;
}


u32 max(u32 x, u32 y) {
    return x > y ? x : y;
}


u32 min(u32 x, u32 y) {
    return x < y ? x : y;
}


int cmpAsc(const void *a, const void *b) {
    const u32 *ptr_a = (const u32*)a;
    const u32 *ptr_b = (const u32*)b;

    if (*ptr_a < *ptr_b) {
        return -1;
    }
    else if (*ptr_a > *ptr_b) {
        return 1;
    }
    else {
        return 0;
    }
}


int cmpDesc(const void *a, const void *b) {
    const u32 *ptr_a = (const u32*)a;
    const u32 *ptr_b = (const u32*)b;

    if (*ptr_a > *ptr_b) {
        return -1;
    }
    else if (*ptr_a < *ptr_b) {
        return 1;
    }
    else {
        return 0;
    }
}
