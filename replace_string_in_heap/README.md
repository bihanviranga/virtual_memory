# Replace string in heap
-----

There are 3 files. They are meant to demonstrate how a string in a file can be changed during runtime using an external script.

`print_str_addr.c` is a basic example. It creates a string in heap using `strdup` (which uses `malloc`) and prints the string's address.

`print_str_addr_loop.c` is the same example, looped forever. While this program is running, the Python script will attempt to change the string in heap.

`replace_string_in_heap.py` is the script that, given a PID, find a string in the heap and replaces it with a given string.

