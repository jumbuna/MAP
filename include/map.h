#include <stdio.h>

typedef int (*hasher)();
typedef int (*comparator)();

struct Map {
    const int limit;
    unsigned size;
    hasher hashfunction;
    comparator comparisonfun;
    void *table[1];
};

struct Map *mapcreate(int, hasher, comparator);
void *mapentrycreate(unsigned long);
void mapaddentry(struct Map *, void *);
unsigned mapsize(struct Map *);
void *mapfindentry(struct Map *, void *);
void *mapnextentry(struct Map *, void *);
void mapremoveentry(struct Map *, void *);
void mapentryfree(void *);
int mapprint(struct Map *, int(*)(), void *);