#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * main - print locations of data.
 *
 * return - EXIT_SUCCESS. If something fails EXIT_FAILURE
 *
 */

int main(int argc, char **argv, char **env) {
	int a;
	void *p;
	int i;

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
	printf("Address of the arguments array: %p\n", (void *)argv);
	printf("Addresses of the arguments:\n\t");
	for(i = 0; i < argc; i++) {
		printf("[%s]:%p ", argv[i], argv[i]);
	}
	printf("\n");
	printf("Address of the array of environment variables: %p\n", (void *)env);
	printf("Address of the first environment variable: %p\n", (void *)(env[0]));

	return(EXIT_SUCCESS);
}