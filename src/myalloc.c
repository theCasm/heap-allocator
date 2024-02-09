#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "myalloc.h"

static RegionHeader *HEAD = NULL;
static RegionHeader *TAIL = NULL;

extern size_t hash(void *addr);

// returns header of appropriate size and hash
static RegionHeader *findHeader(size_t size)
{
	for (RegionHeader *curr = HEAD; curr != NULL; curr = curr->next) {
		if (curr->inUse) {
			continue;
		}

		if (curr->size >= size) {
			// TODO: split chunk
			return curr;
		}
	}

	RegionHeader *res = (RegionHeader *)mmap(NULL,
		size + sizeof(RegionHeader), PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	res->size = size;
	res->hash = hash(res);
	return res;
}

void *myalloc(size_t size)
{
	RegionHeader *mem = findHeader(size);	
	mem->inUse |= 1;
	mem->next = NULL;

	if (HEAD == NULL) {
		HEAD = mem;
		TAIL = mem;
	} else {
		TAIL->next = mem;
		mem->prev = TAIL;
		TAIL = mem;
	}

	return (void *)((uintptr_t)mem + sizeof(RegionHeader));
}

void myfree(void *ptr)
{
	RegionHeader *curr = \
		(RegionHeader *)((uintptr_t)ptr - sizeof(RegionHeader));

	if (hash((void*)curr) != curr->hash) {
		// trying to free bad mem is fatal error
		fputs("Bad free\n", stderr);
		exit(-1);
	}

	curr->inUse &= 0;
}
