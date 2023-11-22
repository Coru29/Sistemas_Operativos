#include "my_malloc_manager.h"
#include "string.h"

void *my_malloc(size_t nbytes)
{
    int units_needed = (nbytes + sizeof(AllocationHeader) + UNIT_SIZE - 1) / UNIT_SIZE;
    int is_large = 0;


    int era_la_primera = -1;
    // si me pasan mas unidades que un chunk precizo un is_large allocation
    if (units_needed > UNITS_PER_CHUNK)
    {
        is_large = 1;
    }
    printf("\n- is_large = %d\n", is_large);
    // convertimos los bytes a unidades

    printf("- Malloc units_needed %d\n", units_needed);

    int bit_index = 0;

    if (first_chunk == NULL)
    {
        printf("METI UNA PRIMERA");
        first_chunk = create_new_chunk(units_needed, is_large, NULL);
        era_la_primera = 1;
    }

    MemoryChunkHeader *chunk = NULL;

    for (chunk = first_chunk; chunk != NULL; chunk = chunk->next)
    {

        if (chunk->is_large_allocation == 1)
            continue;

        bit_index = first_fit(chunk->bitmap, BITMAP_SIZE, units_needed);
        if (bit_index != -1)
        {
            printf("\nSe alocaron correctamente en la posicion %d\n", bit_index);
            break;
        }
        else
        {
            printf("\nNo hay espacio suficiente\n");
        }
    }
    if (era_la_primera && is_large)
    {   
        // le restamos la cantidad de unidades disponibles a partir de lo que alojamos.
        size_t offset = bit_index * UNIT_SIZE;
        AllocationHeader *allocation_header = (AllocationHeader *)((char *)chunk->addr + offset);
        allocation_header->nunits = units_needed;
        allocation_header->bit_index = bit_index;
        chunk->chunk_available_units -= units_needed;

        printf("\n Id del chunk: %u\n", chunk->id);
        printf("\n Unidades totales del chunk:  %u\n", chunk->chunk_total_units);
        printf("\n Unidades disponibles en el chunk: %u \n ", chunk->chunk_available_units);
        
        return (char *)allocation_header + sizeof(AllocationHeader);
    }
    
    if (chunk == NULL)
    {
        // se busca en los bloques existentes un espacio adecuado.
        // Si no se encuentra, se crea un nuevo bloque de memoria.
        printf("\nNo se encontraron chunks con espacio suficente -> %d \n", is_large);
        first_chunk->next = create_new_chunk(units_needed, is_large, first_chunk->next);
        chunk = first_chunk->next;
        // VOLVER A CREAR CHUNK 0 A MANOPLA
        if (!is_large)
        {

            bit_index = first_fit(chunk->bitmap, chunk->bitmap_size, units_needed);
            if (bit_index != -1) // Esto siempre tendria que funcionar,pero checkeo por las dudas
            {
                // Se alocaron correctamente en el nuevo chunk
            }
            else
            {
                printf("No hay espacio en el nuevo chunk"); // No se encontro espacio ni en un nuevo chunk
            }
        }
    }
    // le restamos la cantidad de unidades disponibles a partir de lo que alojamos.
    size_t offset = bit_index * UNIT_SIZE;
    AllocationHeader *allocation_header = (AllocationHeader *)((char *)chunk->addr + offset);
    allocation_header->nunits = units_needed;
    allocation_header->bit_index = bit_index;
    chunk->chunk_available_units -= units_needed;
    printf("\n Id del chunk: %u\n", chunk->id);
    printf("\n Unidades totales del chunk:  %u\n", chunk->chunk_total_units);
    printf("\n Unidades disponibles en el chunk: %u \n ", chunk->chunk_available_units);

    if (!is_large)
    {
        print_bitmap(chunk->bitmap, BITMAP_SIZE);
    }
    else
    {
        printf("\nis_large_allocation -> True \n");
    }

    return (char *)allocation_header + sizeof(AllocationHeader);
}
