#ifndef MYALLOC_H_
#define MYALLOC_H_

typedef struct RegionHeader RegionHeader;
struct RegionHeader {
	size_t size;
	size_t hash;
	RegionHeader *prev;
	RegionHeader *next;
};

void *myalloc(size_t);
void myfree(void*);

#endif
