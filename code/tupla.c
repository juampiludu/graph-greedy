#include <stdlib.h>
#include "tupla.h"

struct TuplaSt {
    u32 arg1;
    u32 arg2;
};

Tupla crearTupla(u32 arg1, u32 arg2) {
    struct TuplaSt *t = malloc(sizeof(struct TuplaSt));
    t->arg1 = arg1;    
    t->arg2 = arg2;    
    return t;
}


Tupla rotarTupla(Tupla t){
    if (t==NULL) {
        exit(EXIT_FAILURE);
    }
    
    struct TuplaSt *tn = malloc(sizeof(struct TuplaSt));
    tn->arg1 = t->arg2;    
    tn->arg2 = t->arg1;
    return tn;    
}

void modifArg1Tupla(Tupla t, u32 elem) {
    t->arg1 = elem;
}

void modifArg2Tupla(Tupla t, u32 elem) {
    t->arg2 = elem;
}

u32 arg1Tupla(Tupla t) {
    return t->arg1;
}

u32 arg2Tupla(Tupla t) {
    return t->arg2;
}

int compararTuplasAsc(const void *t1, const void *t2) {
    const Tupla *tupla1 = (Tupla*) t1;
    const Tupla *tupla2 = (Tupla*) t2;

    if (arg1Tupla(*tupla1) < arg1Tupla(*tupla2)) {
        return -1;
    } else if (arg1Tupla(*tupla1) > arg1Tupla(*tupla2)) {
        return 1;
    } else {
        if (arg2Tupla(*tupla1) < arg2Tupla(*tupla2)) {
            return -1;
        } else if (arg2Tupla(*tupla1) > arg2Tupla(*tupla2)) {
            return 1;
        } else {
            return 0;
        }
    }
}

int compararTuplasDesc(const void* t1, const void* t2) {
    Tupla *tupla1 = (Tupla *) t1;
    Tupla *tupla2 = (Tupla *) t2;
    if (arg2Tupla(*tupla1) == arg2Tupla(*tupla2)) 
        return arg1Tupla(*tupla2) - arg1Tupla(*tupla1);
    return arg2Tupla(*tupla2) - arg2Tupla(*tupla1);
}

Tupla destruirTupla(Tupla t) {
    free(t);
    t = NULL;
    return t;
}


// (1,2) (1,5) (1,3) (1,4)