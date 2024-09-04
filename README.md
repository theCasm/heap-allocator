# heap-allocator
Linux-platfrom basic heap memory allocator. Memory is obtained via mmap and stored as an entry in a linked list. When new memory is requested, a search is performed through the list to see if a now freed block can be reused.
