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
# This is the initial string. We will try to replace this
# in the memory before it prints again below.

print(hex(id(s)))
# This prints the address of the s,
# which is a bytes OBJECT.

sys.stdin.read(1)
# A dramatic pause, before the trick.

print(s)
# Tada! The string should be changed by this point.
