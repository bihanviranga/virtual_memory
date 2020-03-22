"""
Print a bytes string (b"string"),
and then read a char from stdin
and prints the same string again.
"""

import sys
import ctypes

# Import the C library
lib = ctypes.CDLL('./libPython.so')
lib.print_python_bytes.argtypes = [ctypes.py_object]

s = b"VirtualMemory"
print(hex(id(s)))
print(s)
lib.print_python_bytes(s)

sys.stdin.read(1)

print(hex(id(s)))
print(s)
lib.print_python_bytes(s)