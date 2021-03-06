#include "../include/map.h"
#include "allocator/allocator.h"
#include <stdlib.h>

typedef struct Map MAP;

typedef struct Entry {
    struct Entry *next, **prev;
} ENTRY;

MAP *mapcreate(limit, hashfunction, compare, typesize)
int limit;
hasher hashfunction;
comparator compare;
size_t typesize;
{
    MAP *new;
    if((new = (MAP *) calloc(1, sizeof(ENTRY*)*limit + sizeof(MAP)))) {
        *((int *)(new)) = limit;
        new->comparisonfun = compare;
        new->hashfunction = hashfunction;
        ((size_t *)(((int *) new)+2))[2] = (size_t) allocatorcreate(sizeof(ENTRY)+typesize);
    }
    return new;
}

void *mapmalloc(MAP *m) {
    ENTRY *e;
    if((e = allocatorcalloc((struct Allocator *) m->alloc) )) {
        e++;
    }
    return e;
}

void mapfree(MAP *m, void *p) {
    ENTRY *e = ((ENTRY*)(p)-1);
    allocatorfree((struct Allocator *) m->alloc ,e);
}

void mapadd(MAP *m, void *i) {
    ENTRY *e = ((ENTRY *)(i))-1;
    ENTRY **p, *temp;
    p = (ENTRY**) &(m->table)[(*m->hashfunction)(i)% m->limit];
    temp = *p;
    *p = e;
    e->prev = p;
    e->next = temp;
    if(temp) {
        temp->prev = &e->next;
    }
    m->size++;
}

void *mapfind(MAP *m, void *p) {
    ENTRY *e = ((ENTRY *) p)-1;
    ENTRY *ti = (m->table)[(*m->hashfunction)(p) % m->limit];
    while(ti) {
        if((*m->comparisonfun)(ti+1, p) == 0) {
            return ti+1;
        }
        ti = ti->next;
    }
    return 0;

}

void *mapnext(MAP *m, void *p) {
    ENTRY *e = (((ENTRY *) p)-1)->next;
    while(e) {
        if((*m->comparisonfun)(e+1, p) == 0) {
            return e-1;
        }
        e = e->next;
    }
    return 0;
}

void mapremove(struct Map *m, void *p) {
    ENTRY *e = ((ENTRY *) p)-1;
    *(e->prev) = e->next;
    if(e->next) {
        e->next->prev = e->prev;
    }
    --m->size;
}

unsigned mapsize(struct Map *m) {
    return m->size;
}

int mapprint(struct Map *m, int (*print)(), void *param) {
    if(!m || !m->size) {
        return 0;
    }
    for( int i = 0; i < m->limit; i++) {
        ENTRY *e = m->table[i];
        while(e) {
            (*print)(param, e+1);
            e = e->next;
        }
    }

    return 1;
}

//Hashing algorithms
unsigned hashadd(char *c) {
    int count = 0;
    for(count = 0; *c; count += *c++);
    return count;
}