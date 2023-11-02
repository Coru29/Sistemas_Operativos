#include "my_malloc_manager.h"


// Esta función imprime el bitmap en el formato solicitado.
 void print_bitmap(unsigned char *bitmap, size_t bitmap_size){
    for (size_t i = 0; i < bitmap_size; i++) {
        for (size_t j = 0; j < 8; j++) {
            printf("%d", (bitmap[i] >> (7 - j)) & 1);
        }
        printf(" ");
    }
    printf("\n");
}