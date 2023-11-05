#include "my_malloc_manager.h"



void clear_bits(Bitmap bitmap,  uint16_t start_byte_index, uint16_t start_bit_index, uint16_t qty){
    
    if (start_byte_index>15) {
        printf("clear_bits: WRONG! Es hasta 16 bytes ");
        return;
    };
    if (start_bit_index>7) {
        printf("clear_bits: WRONG! Es hasta 8 bits ");
        return;
    };

    char bitmap_en_binario[BITMAP_SIZE * 8];

    lista_decimal_a_binario(bitmap, bitmap_en_binario ,BITMAP_SIZE);
    int start_index = (start_byte_index * 8) + start_bit_index;
    
    for(int i = start_index ; i < start_index + qty; i++) {
        bitmap_en_binario[i] = 0;
    }

    lista_binario_a_decimal(bitmap, bitmap_en_binario, BITMAP_SIZE);

    return;
}