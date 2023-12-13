#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "myalloc.h"

static RegionHeader *HEAD = NULL;
static RegionHeader *TAIL = NULL;

extern size_t hash(void *addr);

void *myalloc(size_t size)
{
	RegionHeader *mem = (RegionHeader *)mmap(NULL,
		size + sizeof(RegionHeader), PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE,
		-1, 0);
	
	mem->size = size;
	mem->hash = hash(mem);
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
		// if u try to free bad mem, u should want it to fail so u know
		fputs("Bad free\n", stderr);
		exit(-1);
	}

	// TODO: preserve memory for re-use

	if (curr->prev != NULL) {
		curr->prev->next = curr->next;
	} else {
		HEAD = curr->next;
	}
	if (curr->next != NULL) {
		curr->next->prev = curr->prev;
	} else {
		TAIL = curr->prev;
	}

	munmap(curr, curr->size + sizeof(RegionHeader));
}
