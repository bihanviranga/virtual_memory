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

	printf("Address of a: %p\n", (void *)&a);

	return(EXIT_SUCCESS);
}