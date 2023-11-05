#ifndef MY_ALLOC_MANAGER_H // prevent multiple includes
#define MY_ALLOC_MANAGER_H 1

// Standard includes
#include <errno.h>  // for errno
#include <stddef.h> // for size_t
#include <stdio.h>  // for I/O functions
#include <stdlib.h> // for EXIT_FAILURE
#include <string.h> // for string manipulation functions
#include <stdint.h> // for uint16_t

#define BITMAP_SIZE 16 // in bytes

#endif // MY_ALLOC_MANAGER_H

typedef unsigned char *Bitmap;

int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed);
void print_bitmap(unsigned char *bitmap, size_t bitmap_size);
void clear_bits(Bitmap bitmap,  uint16_t start_byte_index, uint16_t start_bit_index, uint16_t qty);

// Utils
void lista_decimal_a_binario(unsigned char *bitmap, char *lista_en_binario, size_t bitmap_size);
void lista_binario_a_decimal(unsigned char *bitmap, char *lista_en_binario, size_t bitmap_size);
