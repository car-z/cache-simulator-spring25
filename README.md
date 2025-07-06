# cache-simulator-spring25

Implementing a program to simulate how differenty types of caches perform on different traces.

Possible cache configurations (given in the command line):  
    - number of blocks in each set (positive power-of-2)
    - number of bytes in each block (positive power-of-2, at least 4)
    - write-allocate
    - no-write-allocate
    - write-through
    - write-back
    - lru (least-recently-used) evictions 
    - fifo evictions