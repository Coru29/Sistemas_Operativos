#include "my_malloc_manager.h"

void lista_decimal_a_binario(unsigned char *bitmap, char *lista_en_binario, size_t bitmap_size)
{
    for (size_t i = 0; i < bitmap_size; i++)
    {
        char byte_binario[] = {0, 0, 0, 0, 0, 0, 0, 0};
        int indice = 7;

        while (bitmap[i] > 0)
        {
            byte_binario[indice] = bitmap[i] % 2;
            bitmap[i] /= 2;
            indice--;
        }

        for (size_t j = 0; j < 8; j++)
        {
            lista_en_binario[(i * 8) + j] = byte_binario[j];
        }
    }
}

void lista_binario_a_decimal(unsigned char *bitmap, char *lista_en_binario, size_t bitmap_size)
{
    for (size_t i = 0; i < bitmap_size; i++)
    {
        unsigned char decimal = 0;
        for (int j = 0; j < 8; j++)
        {
            decimal <<= 1;
            decimal |= lista_en_binario[(i * 8) + j];
        }
        bitmap[i] = decimal;
    }
}