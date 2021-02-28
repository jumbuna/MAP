#include <stdio.h>
#include <allocator/allocator.h>

typedef int (*hasher)();
typedef int (*comparator)();

struct Map {
    const int limit;
    unsigned size;
    hasher hashfunction;
    comparator comparisonfun;
    const void *alloc;
    void *table[1];
};

struct Map *mapcreate(int, hasher, comparator, size_t);
void *mapentrycreate(struct Map *);
void mapaddentry(struct Map *, void *);
unsigned mapsize(struct Map *);
void *mapfindentry(struct Map *, void *);
void *mapnextentry(struct Map *, void *);
void mapremoveentry(struct Map *, void *);
void mapentryfree(struct Map *, void *);
int mapprint(struct Map *, int(*)(), void *);