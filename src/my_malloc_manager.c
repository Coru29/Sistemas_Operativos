#include "my_malloc_manager.h"
int set_or_clear_bits(int set, Bitmap bitmap, uint16_t start_byte_index, uint16_t start_bit_index, uint16_t qty) {
    for (int i = 0; i < qty; i++) {
        size_t bit_pos = (start_byte_index * 8 + start_bit_index + i);
        size_t byte_index = bit_pos / 8;
        size_t bit_index = bit_pos % 8;

        if (set) {
            bitmap[byte_index] |= 1 << (7 - bit_index);
        } else {
            bitmap[byte_index] &= ~(1 << (7 - bit_index));
        }
    }
    return 0; // Success
}

int main()
{   
    int opcion = -1; 
    int cantidad_a_poner;
    first_chunk = create_new_chunk(UNITS_PER_CHUNK * UNIT_SIZE, 0, NULL);

   //unsigned char *bitmap = (unsigned char *)first_chunk->bitmap;
    // Get and save the number the user types

    while (opcion != 0)
    {
        printf("\n - Opcion 1: Allocar en bytes \n - Opcion 2: Liberar\n - Opcion 0: SALIR\n");

        printf("\n Opcion: ");
        scanf("%d", &opcion);

        if (opcion == 1)
        {
            printf("\nCantidad de bytes a allocar: ");
            scanf("%d", &cantidad_a_poner);
            void * resultado = my_malloc(cantidad_a_poner);
            printf("Puntero malloc -> %p \n", resultado);
            //print_bitmap(first_chunk->bitmap, BITMAP_SIZE);
        }

        if (opcion == 2)
        {
            printf("\nIngresa el puntero para liberar: ");
            void *ptrFree;
            if (scanf("%p", &ptrFree) != 1) {
                printf("\nInvalid input.\n");
            }
            my_free(ptrFree);
            //print_bitmap(first_chunk->bitmap, BITMAP_SIZE);
        }
    }
    return 0;
}