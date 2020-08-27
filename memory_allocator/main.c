#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

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
	/* Because block is a void*, we don't have to cast
	 * i.e header = (header_t *)block; is not needed. */	
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

/*
 * Frees a memory block allocated with custom malloc() above.
 * If the block is at the end of the heap, the memory is
 * released to the OS.
 * Otherwise the block is marked as free for reallocation by malloc.
 */
void free(void *block) {
	header_t *header, *tmp;
	void *program_break;

	if (!block) {
		return;
	}

	pthread_mutex_lock(&global_malloc_lock);
	/* Cast the block to a header_t and move it behind 
	 * by 1 unit. Because of the cast, size of 1 unit is 
	 * the size of a header_t, which gives us our header. */
	header = (header_t *)block - 1;

	program_break = sbrk(0);

	/* Determine if we are at the end of the heap. */
	/* The reasons for the (char*) cast:
	 * header->s.size is in bytes.
	 * Arithmetic on void* is illegal. */
	if ((char*)block + header->s.size == program_break) {
		/* Only 1 block in linked list */
		if (head == tail) {
			head = tail = NULL;
		} else {
			tmp = head;
			while (tmp) {
				if (tmp->s.next == tail) {
					/* Since we are at the end of the heap */
					tmp->s.next = NULL;
					tail = tmp;
				}
				tmp = tmp->s.next;
			}
		}
		/* Release the memory back to the OS by shrinking
		 * the size of available heap memory */
		sbrk(0 - sizeof(header_t) - header->s.size);
		pthread_mutex_unlock(&global_malloc_lock);
		return;
	}

	/* If we are not at the end of the heap,
	 * just mark it as free. */
	header->s.is_free = 1;
	pthread_mutex_unlock(&global_malloc_lock);
}

/*
 * Allocates memory for an array of num size, with each member being
 * nsize bytes large.
 * Returns a pointer to the allocated memory.
 * Returns NULL if allocation failed.
 */
void *calloc(size_t num, size_t nsize) {
	size_t size;
	void *block;

	if (!num || !nsize) {
		return NULL;
	}

	size = num * nsize;
	/* Check if the multiplication overflowed. */
	if (nsize != size / num) {
		return NULL;
	}

	block = malloc(size);
	if (!block) {
		return NULL;
	}

	memset(block, 0, size);
	return block;
}

