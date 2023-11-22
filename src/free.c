#include "my_malloc_manager.h"

void my_free(void *ptr)
{
    int id_a_sacar = -1;
    if (!ptr)
    {
        // Si el ptr es NULL, no hacer nada
        return;
    }
    // necesitamos encontrar el chunk a partir del pointer

    /// obtenemos el header del malloc, sabiendo que si tengo el puntero del malloc y le resto el tamaño del header obtengo la posicion del header
    AllocationHeader *header = (AllocationHeader *)(((char *)ptr) - sizeof(AllocationHeader));

    // Obtener el encabezado del primer bloque de memoria para poder movernos
    MemoryChunkHeader *chunk = first_chunk;

    while (chunk != NULL)
    {
        // El puntero tiene que estar entre el puntero de address del chunk y la cantidad de unidades del mismo chunk
        if ((ptr > chunk->addr) && (ptr < chunk->addr + (chunk->chunk_total_units * UNIT_SIZE)))
        {
            printf("\n\n\nEncontre el chunk\n\n");
            break;
        }
        // no era este chunk me sigo moviendo en mi lista
        chunk = chunk->next;
        printf("\nPase de chunk\n");
    }

    // Calcular el índice de inicio en el bitmap basado en el AllocationHeader
    uint16_t start_byte_index = header->bit_index / 8;
    uint16_t start_bit_index = header->bit_index % 8;

    // Actualizar el contador de unidades disponibles en el chunk
    chunk->chunk_available_units += header->nunits;
    // Poner en cero los bits en el bitmap para representar el espacio como libre
    set_or_clear_bits(0, chunk->bitmap, start_byte_index, start_bit_index, header->nunits);
    // mostramos como queda el bitmap del chunk
    printf("\n Id del chunk: %u\n", chunk->id);
    printf("\n Unidades totales del chunk:  %u\n", chunk->chunk_total_units);
    printf("\n Unidades disponibles en el chunk: %u \n ", chunk->chunk_available_units);
    print_bitmap(chunk->bitmap, BITMAP_SIZE);
    if ((chunk->chunk_available_units == UNITS_PER_CHUNK - (sizeof(MemoryChunkHeader) / UNIT_SIZE) - 2) && (chunk->id != 0))
    { // tengo que sacar este chunk esta vacio
        id_a_sacar = chunk->id;
    }
    if (id_a_sacar != -1 && first_chunk != NULL)
    {
        MemoryChunkHeader *chunk2 = first_chunk;

        while (chunk2->next != NULL)
        {
            if (chunk2->next->id == id_a_sacar)
            {
                MemoryChunkHeader *temp = chunk2->next;
                printf("Se borro el chunk: %d\n", temp->id);
                chunk2->next = temp->next;
                return; // Exit the function after successful removal
            }

            chunk2 = chunk2->next;
        }

        printf("No se encontro el chunk con el ID especificado.\n");
    }
}
