#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include "APIParte3.h"

void printArray(u32 *arr, u32 len);

void printNombres(Grafo G);

void printTuplaArg(Tupla *arr, u32 len, u32 (*fun)(Tupla));

void mergeArrays(u32 *arr1, u32 len1, u32 *arr2, u32 len2, u32 *target);

u32 *copyArray(u32 *src, u32 len);

u32 max(u32 x, u32 y);

u32 min(u32 x, u32 y);

int cmpAsc(const void *a, const void *b);

int cmpDesc(const void *a, const void *b);

#endif