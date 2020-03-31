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
	unsigned int i;

	p = malloc(98);
	if(p == NULL) {
		fprintf(stderr, "Can't allocate memory\n");
		return(EXIT_FAILURE);
	}

	printf("Address of a: %p\n", (void *)&a);
	printf("Allocated space in the heap: %p\n", p);
	printf("Address of function main: %p\n", (void *)main);
	printf("First bytes of the main function:\n\t");
	for(i = 0; i < 15; i++) {
		printf("%02x ", ((unsigned char *)main)[i]);
	}
	printf("\n");

	return(EXIT_SUCCESS);
}