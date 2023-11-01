#include "my_malloc_manager.h"

void decimal_a_binario(unsigned char *bitmap, int *binario, int index){
    for (int i = 7; i >= 0; i--) {
        binario[index + i] = *bitmap & 1;
        *bitmap >>= 1;
    }
}

// Esta función busca un hueco de tamaño units_needed en el bitmap.
int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed) {
    
    int enbinario[bitmap_size * 8];


    for (int i = 0; i < bitmap_size; i++) {
        decimal_a_binario(bitmap, enbinario, i * 8);
    }

    for (size_t i = 0; i < bitmap_size * 8; i++)
    {
        printf("%i",enbinario[i]);
    }
    
}