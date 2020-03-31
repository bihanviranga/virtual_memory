#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * main - print locations of data.
 *
 * return - EXIT_SUCCESS. If something fails EXIT_FAILURE
 *
 */

int main(void) {
	int a;
	void *p;

	p = malloc(98);
	if(p == NULL) {
		fprintf(stderr, "Can't allocate memory\n");
		return(EXIT_FAILURE);
	}

	printf("Address of a: %p\n", (void *)&a);
	printf("Allocated space in the heap: %p\n", p);

	return(EXIT_SUCCESS);
}