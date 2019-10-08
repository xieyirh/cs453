#include <stdlib.h> 

#define MAX_MEMORY_SIZE (1ll << 35) 
#define DEF_MEMORY_SIZE (1ll << 29)
#define DEF_INDEX 30
#define MAX_INDEX 36

typedef struct Headers{
    struct Headers *prev;
    int tag;
    unsigned int  kval;
    struct Headers *next;
} Header;

void buddy_init(size_t);
void *buddy_malloc(size_t);
void *buddy_realloc(void *ptr, size_t size);
void buddy_free(void *);
void *buddy_calloc(size_t, size_t);
/*
void *calloc(size_t, size_t);
void *malloc(size_t);
void *realloc(void *ptr, size_t size);
void free(void *);
*/
void *buddy_memcp(void*, const void*, size_t );

void printBuddyLists();

