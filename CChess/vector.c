#include "vector.h"

void v_display(vector_i* v){
    int i=0;
    printf("[ ");
    if(v)
    for(i=0;i<v->size(v); i++){
        printf("%d ",v->get(v,i));
    }
    printf("]\n");
}

int vSize(vector_i *v){
    int v_size = 0;
    if(v){
        v_size = v->total;
    }
    return v_size;
}
int vResize(vector_i *v, int capacity){
    int  status = UNDEFINE;
    if(v)
    {
        int *items = (int*)realloc(v->items, sizeof(int) * capacity);
        if (items){
            v->items = items;
            v->capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}
int vAppend(vector_i *v, int item){
    int  status = UNDEFINE;
    if(v){
        if (v->capacity == v->total){
            status = vResize(v, v->capacity * 2);
            if(status != UNDEFINE){
                v->items[v->total++] = item;
            }
        }
        else{
            v->items[v->total++] = item;
            status = SUCCESS;
        }
    }
    return status;
}
int vExtend(vector_i* v, vector_i* n){
    int status = UNDEFINE;
    if(v){
        if(v->capacity <= v->total+n->total){
            status = vResize(v, v->capacity+n->total);
            if(status == UNDEFINE){
                return status;
            }
        }
        
        int i=0;
        for(i=0;i<n->total;i++)
            v->items[v->total++] = n->items[i];
    
    }
    return status;
} 
int vSet(vector_i *v, int index, int item){
    int  status = UNDEFINE;
    int i= index;
    if(v){
        if(index < 0) 
            i = v->total+i;
        if ((i >= 0) && (i < v->total)){
            v->items[i] = item;
            status = SUCCESS;
        }
        else{
            printf("\nIndexOutOfBound: vector size %d got index %d", v->total, index);
            v->free(v);
            exit(1);
            
        }
    }
    return status;
}
int vGet(vector_i *v, int index){
    int readData = -1, i=index;
    if(v){
        if(index < 0) 
            i = v->total+i;
        if ((i >= 0) && (i < v->total))
        {
            return readData = v->items[i];
        }
        else{
            printf("\nIndexOutOfBound: vector size %d got index %d", v->total, index);
            v->free(v);
            exit(1);
            
        }
    }
    return readData;
}
int vPop(vector_i *v, int index){
    int  status = UNDEFINE;
    int i = 0;
    if(v){
        if ((index < 0) || (index >= v->total))
            return status;
        v->items[index] = 0;
        for (i = index; (i < v->total - 1); ++i){
            v->items[i] = v->items[i + 1];
            v->items[i + 1] = 0;
        }
        v->total--;
        if ((v->total > 0) && ((v->total) == (v->capacity / 4))){
            vResize(v, v->capacity / 2);
        }
        status = SUCCESS;
    }
    return status;
}
int vClear(vector_i* v){
    int  status = UNDEFINE;
    if(v){
        free(v->items);
        v->capacity = VECTOR_INIT_CAPACITY;
        v->total = 0;
        v->items = malloc(sizeof(int) * v->capacity);
        status = SUCCESS;
    }
    return status;
}

bool v_find(vector_i* v_vec, int key){
    int found = false;
    if(v_vec){
        int i=0;
        for(i=0;i<v_vec->total;i++)
            if (v_vec->items[i] == key){
                found=true;
                break;
            }
        
    }
    return found;
}

int vFree(vector_i *v){
    int  status = UNDEFINE;
    if(v){
        free(v->items);
        v->items = NULL;
        v->total=0;
        status = SUCCESS;
    }
    return status;
}


void vector_init(vector_i *v)
{
    v->size = vSize;
    v->resize = vResize;
    v->append = vAppend;
    v->set = vSet;
    v->get = vGet;
    v->free = vFree;
    v->pop_at = vPop;
    v->display = v_display;
    v->extend = vExtend;
    v->clear = vClear;
    v->capacity = VECTOR_INIT_CAPACITY;
    v->total = 0;
    v->items = malloc(sizeof(int) * v->capacity);
}
int runVectorTest()
{
    int i = 0;
    VECTOR_INIT(v);
    VECTOR_INIT(t);
    v.append(&v, 1);
    v.append(&v, 2);
    v.append(&v, 3);
    v.display(&v);
    printf("%d ",v.get(&v,-2));
    v.set(&v, 2, 20);
    v.display(&v);
    
    t.extend(&t, &v);
    t.display(&t);
    v.free(&v);
    printf("INFO: All test passed");
    return 0;
}

