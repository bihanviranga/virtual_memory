# Memory regions

## Programs

### main-0.c
Gets the address of a variable `a` to determine the general memory region of the stack.

### main-1.c
Extension of above. Gets the address of a memory location reserved with `malloc`.

### main-2.c
Extension of above. Gets the address of the main function.

Bytes of the main function obtained with `objdump -M intel -j .text -d main-2 | grep '<main>:' -A 5 > objdump_output.txt`

### main-3.c
Extension of above. Prints the first few bytes of the main function to compare it against the objdump output produced previously.

### main-4.c
Extension of above. Prints the addresses of the argv array and env array, with the addresses of each argument.

## Compilation

### main-0.c main-1.c
`gcc -Wall -Wextra -pedantic -Werror main-0.c -o main-0`

### main-2.c to main-4.c
`gcc -Wall -Wextra -Werror main-2.c -o main-2`

## Environment

- gcc version 9.3.0 (Arch Linux 9.3.0-1) 
- Arch Linux (5.5.13-arch1-1)
- GNU objdump (GNU Binutils) 2.34
