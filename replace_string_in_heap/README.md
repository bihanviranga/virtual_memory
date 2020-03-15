# Replace string in heap

There are 3 files. They are meant to demonstrate how a string in a file can be changed during runtime using an external script.

`print_str_addr.c` is a basic example. It creates a string in heap using `strdup` (which uses `malloc`) and prints the string's address.

`print_str_addr_loop.c` is the same example, looped forever. While this program is running, the Python script will attempt to change the string in heap.

`replace_string_in_heap.py` is the script that, given a PID, finds a string in the heap and replaces it with a given string.

### Compiling C source
`gcc -Wall -Wextra -pedantic -Werror print_str_addr.c -o print_str_addr`

### Running the Python script
- Requires root permission.
- Uses Python 3
- Find the PID with:
`ps aux | grep print_str | grep -v grep`
- Execute with
`sudo python3 replace_string_in_heap.py [PID] search_str replace_str`
