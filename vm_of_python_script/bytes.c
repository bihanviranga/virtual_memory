#include "Python.h"

/*
 * print_python_bytes:
 * prints info about a Python3 bytes objects
 *
 * p : a pointer to a Python3 bytes object
 *
 * return - nothing
 *
 */

void print_python_bytes(PyObject *p) {
	// The pointer with the correct type.
	PyBytesObject *s;
	unsigned int i;

	printf("[.] Bytes object info\n");

	// Casting the PyObject pointer to a PyBytesObject pointer
	s = (PyBytesObject *)p;

	// Check that it is actually a PyBytesObject object.
	if (s && PyBytes_Check(s)) {
		//  The pointer points to the first byte of the data
		printf("Address of the object: %p\n", (void *) s);
		// ob_size is in ob_base struct, of PyVarObject
		printf("Size: %ld\n", s->ob_base.ob_size);
		// ob_sval is the array of bytes, zero-terminated.
		printf("Trying string: %s\n", s->ob_sval);
		printf("Address of the data: %p\n", (void *)(s->ob_sval));
		printf("Bytes:");
		// Printing one byte at a time,
		// because this might not be a string, in some cases.
		// ob_sval contains space for ob_size+1 elements:
		// ob_sval[ob_size] == 0;
		for (i = 0; i < s->ob_base.ob_size + 1; i++) {
			printf(" %02x", s->ob_sval[i] & 0xff);
		}
		printf("\n");
	}
	// if not a PyBytesObject
	else {
		fprintf(stderr, "[ERROR] Invalid Bytes object.\n");
	}
}
