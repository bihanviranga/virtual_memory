"""
Print a bytes string (b"string"),
and then read a char from stdin
and prints the same string again.
"""

import sys

s = b"VirtualMemory"
# This ensures that we are using a bytes object.
# The string will be saved as bytes, as ASCII values
# in the virtual memory of the script.

print(s)
sys.stdin.read(1)
print(s)
