#include "my_malloc_manager.h"
// Plan de accion:
//-Interfaz
//-Acceder al bitmap
int set_or_clear_bits(int set, Bitmap bitmap, uint16_t start_byte_index, uint16_t start_bit_index, uint16_t qty)
{ // si 1 pone 1 si 0 pone 0
    if (set)
    {
        return first_fit(bitmap, BITMAP_SIZE, qty);
    }
    else
    {
        return clear_bits(bitmap, start_byte_index, start_bit_index, qty);
    }
}

int main()
{
    MemoryChunkHeader *mem = create_new_chunk(UNITS_PER_CHUNK * UNIT_SIZE, 0, NULL);
    unsigned char *bitmap = (unsigned char *)mem->bitmap;
    int opcion;
    int cantidad_a_poner;
    int byte_a_sacar;
    int bits_a_sacar;
    int cantidad_bits_a_sacar;

    // Get and save the number the user types

    while (opcion != 0)
    {
        printf("\n - Opcion 1: ponerla \n - Opcion 2: sacarla\n - Opcion 0: SALIR\n");

        printf("\n Opcion: ");
        scanf("%d", &opcion);

        if (opcion == 1)
        {
            printf("\nCantidad de unidades a allocar: ");
            scanf("%d", &cantidad_a_poner);
            void * resultado = malloc(18);
            if (resultado == -1)
            {
                while (mem->next != NULL)
                {
                    if (first_fit(mem->bitmap, BITMAP_SIZE, cantidad_a_poner) == -1)
                    {
                        mem = mem->next;
                    }
                    else
                    {
                        first_fit(mem->bitmap, BITMAP_SIZE, cantidad_a_poner);
                        break;
                    }
                }
                mem = create_new_chunk(UNITS_PER_CHUNK * UNIT_SIZE, 0, mem);
                resultado = set_or_clear_bits(1, mem->bitmap, 0, 0, cantidad_a_poner);
            }

            print_bitmap( mem->bitmap, BITMAP_SIZE);
        }

        if (opcion == 2)
        {
            printf("En que byte queres sacar: ");
            scanf("%d", &byte_a_sacar);
            printf("\nEn cual bit queres sacar: ");
            scanf("%d", &bits_a_sacar);
            printf("\nCuantos bits queres sacar: ");
            scanf("%d", &cantidad_bits_a_sacar);
            clear_bits(bitmap, byte_a_sacar, bits_a_sacar, cantidad_bits_a_sacar);

            print_bitmap(bitmap, BITMAP_SIZE);
        }
        if (opcion == 0)
        {
            printf("\nchau loco suerte");
        }
    }

    // create_new_chunk(UNITS_PER_CHUNK * UNIT_SIZE,0,NULL);
    // printf("\n Puntero header %p\n", mem);
    // printf ("\n Puntero Bitmap %d\n", *mem->bitmap);
    // printf("\n Size header %ld\n", sizeof(mem));

    // MemoryChunkHeader *actual = (MemoryChunkHeader *)mem.next;

    /*  printf ("\n Puntero header %p\n", actual);
     //printf ("\n Puntero Bitmap %d\n", mem->bitmap[0]);
     printf ("\n Size header %ld\n", sizeof(actual)); */

    // Definiendo el bitmap.
    // Este array va a tener elementos que pueden ir de 0 a 255,
    // esto es genial para representar el bitmap, ya que la representacion
    // binaria de cada elemento tiene 8 bits.

    // Inicializar el bitmap con ceros.
    /* for (size_t i = 0; i < BITMAP_SIZE; i++)
    {
        bitmap[i] = 0;
    } */

    // Imprimir el bitmap.
    /* printf("Bitmap inicial: ");
    print_bitmap(bitmap, BITMAP_SIZE); */

    /* // Hacer varias invocaciones de first_fit y mostrar el resultado.
    int indices[] = {5, 10, 7, 20, 50, 2}; // Ejemplo de tamaños solicitados
    for (long unsigned int i = 0; i < sizeof(indices) / sizeof(indices[0]); i++)
    {
        int result = first_fit(bitmap, BITMAP_SIZE, indices[i]);
        if (result != -1)
        {
            printf("Alojados %d bits en el índice: %d\n", indices[i], result);
        }
        else
        {
            printf("No hay suficiente espacio para %d bits.\n", indices[i]);
        }
        print_bitmap(bitmap, BITMAP_SIZE);
    }

    printf("\n\nPruebas clear_bits \n\n");

    clear_bits(bitmap, 1, 2, 16);

    print_bitmap(bitmap, BITMAP_SIZE);

    printf("\n\nPruebas first_fit \n\n");

    first_fit(bitmap, BITMAP_SIZE, 17);

    print_bitmap(bitmap, BITMAP_SIZE); */

    return 0;
}