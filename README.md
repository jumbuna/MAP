# MAP

## DESCRIPTION
A general purpose hashmap in c.

## INSTALLING
> Currently the only way to obtain this library is by building from source, described in the next section.

## BUILDING
Requirements:
- CMAKE >= v3.19
- Any C compiler
- <a href ="https://github.com/jumbuna/ALLOCATOR" >Allocator library</a>

```bash
$ cd /path/to/repo/clone
$ cmake -B build
$ cmake --build build
# optional
$ cmake --build build --target install
```
## EXAMPLES
```c
typedef struct Map map;
typedef struct Person {
    char name[20];
    int age;
} person;
extern hashadd(char*);
map *mp = mapcreate(10, hashadd, strcmp, sizeof(person));
person *p = mapmalloc(mp);
strcpy(p->name, "jumbuna");
p->age = 100;
mapadd(mp, p);
mapsize(mp); // 1
person *x = mapfind(mp, "jumbuna");
assert(p == x);
/* remove 'jumbuna' from map */
mapremove(mp, p);
/* release 'jumbuna' memory */
mapfree(mp, p);
```
## CONTRIBUTIONS
All contributions are welcome. Send me a pull request anytime.

