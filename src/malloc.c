#include "my_malloc_manager.h"
#include "string.h"

void *my_malloc(int nbytes)
{
    // convertimos los bytes a unidades
    int units_needed = (nbytes + sizeof(AllocationHeader) + UNIT_SIZE - 1) / UNIT_SIZE;
    printf("- Malloc units_needed %d\n", units_needed);
    MemoryChunkHeader *chunk = NULL;
    int bit_index;
    
    if (first_chunk == NULL)
    {
        first_chunk = create_new_chunk(UNITS_PER_CHUNK, 0, NULL); 
    }

    for (chunk = first_chunk; chunk != NULL; chunk = chunk->next)
    {
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
    if (chunk == NULL)
    {
        // se busca en los bloques existentes un espacio adecuado.
        // Si no se encuentra, se crea un nuevo bloque de memoria.
        printf("\nNo se encontraron chunks con espacio suficente \n");
        first_chunk->next = create_new_chunk(units_needed, 0, first_chunk->next);
        chunk = first_chunk->next;
        
        bit_index = first_fit(chunk->bitmap, chunk->bitmap_size, units_needed);
        if(bit_index != 1){ //Esto siempre tendria que funcionar,pero checkeo por las dudas
            //Se alocaron correctamente en el nuevo chunk
        }else{
            printf("No hay espacio en el nuevo chunk");//No se encontro espacio ni en un nuevo chunk
        }
    }
    //le restamos la cantidad de unidades disponibles a partir de lo que alojamos.
    chunk->chunk_available_units -= units_needed;
    size_t offset = bit_index * UNIT_SIZE;
    AllocationHeader *allocation_header = (AllocationHeader *) ((char *) chunk->addr + offset);
    allocation_header->nunits = units_needed;
    allocation_header->bit_index = bit_index;

    print_bitmap(chunk->bitmap, BITMAP_SIZE);
    
    return (char *) allocation_header + sizeof (AllocationHeader);
}