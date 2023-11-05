#ifndef MY_ALLOC_MANAGER_H // prevent multiple includes
#define MY_ALLOC_MANAGER_H 1

// Standard includes
#include <errno.h>  // for errno
#include <stddef.h> // for size_t
#include <stdio.h>  // for I/O functions
#include <stdlib.h> // for EXIT_FAILURE
#include <string.h> // for string manipulation functions

#define BITMAP_SIZE 16 // in bytes

#endif // MY_ALLOC_MANAGER_H

int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed);
void print_bitmap(unsigned char *bitmap, size_t bitmap_size);