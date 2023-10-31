#include "my_malloc_manager.h"


// Esta función busca un hueco de tamaño units_needed en el bitmap.
int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed) {
    char cosas [BITMAP_SIZE * 8];
    
   for (size_t i = 0; i < bitmap_size; i++) {
        for (int j = 0; j < 8; j++) {
            cosas[j + i * 8] = (bitmap[i] >> j) & 1;
        }
    }
}