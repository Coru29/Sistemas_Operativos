#include "my_malloc_manager.h"
#include "string.h"

void *my_malloc(size_t nbytes)
{
    int units_needed = (nbytes + sizeof(AllocationHeader) + UNIT_SIZE - 1) / UNIT_SIZE;
    int is_large = 0;

    // si me pasan mas unidades que un chunk precizo un is_large allocation
    if (units_needed + STRUCT_UNITS > UNITS_PER_CHUNK)
    {
        is_large = 1;
    }
    printf("\n** is_large -> %d", is_large);
    // convertimos los bytes a unidades

    printf("\n** Malloc units_needed -> %d\n", units_needed);

    int bit_index = 0;

    MemoryChunkHeader *chunk = NULL;

    for (chunk = first_chunk; chunk != NULL; chunk = chunk->next)
    {
        if (!is_large && !chunk->is_large_allocation) //
        {
            bit_index = first_fit(chunk->bitmap, BITMAP_SIZE, units_needed);
            if (bit_index != -1)
            {
                printf("\n** Se alocaron correctamente en la posicion %d\n", bit_index);
                break;
            }
            else
            {
                printf("\n** No hay espacio suficiente\n");
            }
        }
    }

    if (chunk == NULL && is_large)
    {
        first_chunk->next = create_new_chunk(units_needed, is_large, first_chunk->next);
        chunk = first_chunk->next; // Actualizo chunk con el nuevo chunk creado

        // le restamos la cantidad de unidades disponibles a partir de lo que alojamos.
        size_t offset = UNIT_SIZE;
        AllocationHeader *allocation_header = (AllocationHeader *)((char *)chunk->addr + offset);
        allocation_header->nunits = units_needed;
        allocation_header->bit_index = bit_index;
        chunk->chunk_available_units -= units_needed;

    printf("\033[32m\n** Id del chunk: %u\033[0m\n", chunk->id);
    printf("\033[32m** Unidades totales del chunk:  %u\033[0m\n", chunk->chunk_total_units);
    printf("\033[32m** Unidades disponibles en el chunk: %u \033[0m\n", chunk->chunk_available_units);

        return (char *)allocation_header + sizeof(AllocationHeader);
    }

    if (chunk == NULL && !is_large)
    {
        // si no se encuentra un chunk con el espacio suficiente se crea otro
        printf("\n** No se encontraron chunks con espacio suficente -> %d \n", is_large);
        first_chunk->next = create_new_chunk(units_needed, is_large, first_chunk->next);
        chunk = first_chunk->next;
        bit_index = first_fit(chunk->bitmap, chunk->bitmap_size, units_needed);
        if (bit_index != -1) // Esto siempre tendria que funcionar,pero checkeo por las dudas
        {
            // Se alocaron correctamente en el nuevo chunk
        }
        else
        {
            printf("** No hay espacio en el nuevo chunk"); // No se encontro espacio ni en un nuevo chunk
        }
    }
    // le restamos la cantidad de unidades disponibles a partir de lo que alojamos.
    size_t offset = bit_index * UNIT_SIZE;
    AllocationHeader *allocation_header = (AllocationHeader *)((char *)chunk->addr + offset);
    allocation_header->nunits = units_needed;
    allocation_header->bit_index = bit_index;
    chunk->chunk_available_units -= units_needed;

    printf("\n ** Id del chunk: %u", chunk->id);
    printf("\n ** Unidades totales del chunk:  %u", chunk->chunk_total_units);
    printf("\n ** Unidades disponibles en el chunk: %u", chunk->chunk_available_units);

    if (!is_large)
    {
        print_bitmap(chunk->bitmap, BITMAP_SIZE);
    }
    else
    {
        printf("\n ** is_large_allocation -> True (No se imprime el bitmap) \n");
    }

    return (char *)allocation_header + sizeof(AllocationHeader);
}
