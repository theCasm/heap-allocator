#ifndef MYALLOC_H_
#define MYALLOC_H_

typedef struct RegionHeader RegionHeader;
struct RegionHeader {
	size_t size;
	size_t hash;
	int inUse;
	RegionHeader *prev;
	RegionHeader *next;
} __attribute__ ((aligned (8)));

void *myalloc(size_t);
void myfree(void*);

#endif
