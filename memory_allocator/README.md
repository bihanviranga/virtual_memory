# C Memory Allocator

The end of the heap is marked by a pointer called the program break, or **brk**. `sbrk()` allows changing the location of program break.

In order to free memory, we have to know the size of the memory 'block' that is allocated by our custom malloc. The idea is, we will add a header to every block of memory allocated, and that header will contain the size of this block.

The block of memory given away by our malloc might be further partitioned by user code containing sbrk() calls. So we need a way to traverse from one block of memory to the next. To do this, we store our memory blocks as a linked list.

The purpose of the ALIGN stub in the header is to ensure memory alignment. Unions always take the space of the larger member.

`get_free_block()` returns a previously allocated and freed block that fits the size requirements. NOTE: This is memory inefficient as it allocates the first-fit, as opposed to the ideal best-fit.

## References
- [link](https://arjunsreedharan.org/post/148675821737/memory-allocators-101-write-a-simple-memory)
- `man sbrk`
