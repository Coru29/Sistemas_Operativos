#include "my_malloc_manager.h"

void lista_decimal_a_binario(unsigned char *bitmap, int *lista_en_binario, size_t bitmap_size){

    for (int i = 0; i < bitmap_size; i++) {
        for (int j = 7; j >= 0; j--) {
            lista_en_binario[(i * 8) + j] = *bitmap & 1;
            *bitmap >>= 1;
        }
    }

}

// Esta función busca un hueco de tamaño units_needed en el bitmap.
int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed) {
    
    int bitmap_en_binario[bitmap_size * 8];


    lista_decimal_a_binario(bitmap, bitmap_en_binario, bitmap_size);

    for (size_t i = 0; i < bitmap_size * 8; i++){
        printf("%i",bitmap_en_binario[i]);
    }
    printf("\n");
}