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

/**
 * Create a new map 
 */
struct Map *mapcreate(int, hasher, comparator, size_t);
/**
 * Pre Allocate memory fro a map bucket
 */
void *mapmalloc(struct Map *);
/**
 * Add the an entry returned by a previous
 * mapmalloc() call
 */
void mapadd(struct Map *, void *);
/**
 * GEt current number of entries in the map
 */
unsigned mapsize(struct Map *);
/**
 * Search the map for an entry matching the
 * given argument
 */
void *mapfind(struct Map *, void *);
/**
 * Find the next entry that matches the given entry.
 * The second parameter should be a pointer returned
 * by either mapfind or mapnext itself.
 */
void *mapnext(struct Map *, void *);
/**
 * Remove an entry from the map.
 */
void mapremove(struct Map *, void *);
/**
 * Free memory allocated by mapmalloc.
 */
void mapfree(struct Map *, void *);
/**
 * print the contents of a map using the provided
 * printing function (param 2).
 */
int mapprint(struct Map *, int(*)(), void *);