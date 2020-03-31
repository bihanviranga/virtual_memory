# Memory regions

## Programs

### main-0.c
Gets the address of a variable `a` to determine the general memory region of the stack.

### main-1.c
Extension of above. Gets the address of a memory location reserved with `malloc`.

## Compilation

Compile with `gcc -Wall -Wextra -pedantic -Werror main-0.c -o main-0`

## Environment

- gcc version 9.3.0 (Arch Linux 9.3.0-1) 
- Arch Linux (5.5.13-arch1-1)

