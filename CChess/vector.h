#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#define VECTOR_INIT_CAPACITY 6
#define UNDEFINE  -1
#define SUCCESS 0

#define bool int
#define true 1
#define false 0
#define and &&
#define or ||
 
typedef struct sVector vector_i;
struct sVector
{
    int *items;
    int capacity;
    int total;
    int (*size)(vector_i *);
    int (*resize)(vector_i *, int);
    int (*append)(vector_i *, int);
    int (*set)(vector_i *, int, int);
    int (*get)(vector_i *, int);
    int (*pop_at)(vector_i *, int);
    int (*pop)(vector_i *);
    int (*clear)(vector_i *);
    int (*free)(vector_i *);
    int (*extend)(vector_i *, vector_i*);
    void (*display)(vector_i* );
};

void vector_init(vector_i* );
bool v_find(vector_i* , int);


#define VECTOR_INIT(vec) vector_i vec;\
 vector_init(&vec)

#define VECTOR_INIT_EXPORT(vec) vector_i* vec = (vector_i*)malloc(sizeof(vector_i)) ;\
 vector_init(vec)

#define FOR(n,vec) int _i=0,n;\
    for(_i=0;_i<vec->size(vec);_i++){\
    n=vec->get(vec, _i); 

#endif