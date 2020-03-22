# Virtual Memory of a Python Script

### Environment
- Python 3.8
- gcc version 9.3.0 (Arch Linux 9.3.0-1) 
- Arch Linux (5.5.9-arch1-2)

### Files : 
**print_byte_string.py**
A simple script which will be used as the basis for testing.

**print_byte_string_v2.py**
A slight improvement over the previous. Nothing fancy.

**print_byte_string_v3.py**
Using a dynamic library, this script prints out the exact location of the memory we are trying to replace.

**bytes.c**
A library to get information about Python3 Bytes Objects.

**replace_bytes_in_vm.py**
This script scans all the regions of the script's virtual memory, to find and replace the string.

### Compiling C source

**bytes.c**
- Compile using: `gcc -Wall -Wextra -pedantic -Werror -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.8 bytes.c`
- Can use the already existing .so file as well.
- This should create a dynamic library caleld `libPython.so`.

### Reference
- `/usr/include/python3.8/bytesobject.h'
- `/usr/include/python3.8/object.h'

