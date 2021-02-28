#include "../include/map.h"
#include <stdlib.h>

typedef struct Map MAP;

typedef struct Entry {
    struct Entry *next, **prev;
} ENTRY;

MAP *mapcreate(limit, hashfunction, compare)
int limit;
hasher hashfunction;
comparator compare;
{
    MAP *new;
    if((new = (MAP *) calloc(1, sizeof(ENTRY*)*limit + sizeof(MAP)))) {
        *((int *)(new)) = limit;
        new->comparisonfun = compare;
        new->hashfunction = hashfunction;
    }
    return new;
}

void *mapentrycreate(unsigned long sz) {
    ENTRY *e;
    if(!(e = calloc(1, sizeof(ENTRY)+sz))) {
        e++;
    }
    return e;
}

void mapentryfree(void *p) {
    ENTRY *e = ((ENTRY*)(p)-1);
    free(e);
}

void mapaddentry(MAP *m, void *i) {
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

void *mapfindentry(MAP *m, void *p) {
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

void *mapnextentry(MAP *m, void *p) {
    ENTRY *e = (((ENTRY *) p)-1)->next;
    while(e) {
        if((*m->comparisonfun)(e+1, p) == 0) {
            return e-1;
        }
        e = e->next;
    }
    return 0;
}

void mapremoveentry(struct Map *m, void *p) {
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