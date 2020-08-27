#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
 * Every allocated block of memory has a header that
 * keeps track of its size, and whether it is allocated or not,
 * and where the next block of memory is.
 */
typedef char ALIGN[16];
union header {
	struct {
		size_t size;
		unsigned is_free;
		union header *next;
	} s;
	ALIGN stub;
};
typedef union header header_t;

/* forward declarations */
header_t *get_free_block(size_t size);

/* To prevent two or more threads concurrently accessing the same memory. */
pthread_mutex_t global_malloc_lock;

/* Keeping track of the linked list */
header_t *head, *tail;

/*
 * Allocates 'size' bytes on the heap.
 * Returns a pointer to the start of the newly allocated memory.
 * On failure, returns NULL.
 */
void *malloc(size_t size) {
	size_t total_size;
	void *block;
	header_t *header;

	if (!size) {
		return NULL;
	}

	pthread_mutex_lock(&global_malloc_lock);
	
	/* Check if a suitable block is already there.
	 * If not, proceed to create new block at the tail-end. */
	header = get_free_block(size);
	if (header) {
		header->s.is_free = 0;
		pthread_mutex_unlock(&global_malloc_lock);
		return (void *)(header + 1);
	}

	total_size = sizeof(header_t) + size;
	block = sbrk(total_size);
	if (block == (void *) -1) {
		pthread_mutex_unlock(&global_malloc_lock);
		return NULL;
	}

	/* Since this is a new block, s.next is NULL */
	header = block;
	header->s.size = size;
	header->s.is_free = 0;
	header->s.next = NULL;
	if (!head) {
		head = header;
	}
	if (tail) {
		tail->s.next = header;
	}
	tail = header;
	
	pthread_mutex_unlock(&global_malloc_lock);
	return (void *)(header + 1);
}

/*
 * Returns a previously freed block of memory.
 * Returns null if no such blocks are available.
 */
header_t *get_free_block(size_t size) {
	header_t *curr = head;
	while(curr) {
		if (curr->s.is_free && curr->s.size >= size) {
			return curr;
		}
		curr = curr->s.next;
	}
	return NULL;
}

