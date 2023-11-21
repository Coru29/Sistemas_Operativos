#include "my_malloc_manager.h"

void my_free(void *ptr) {
    if (!ptr) {
        // Si el ptr es NULL, no hacer nada
        return;
    }
    //necesitamos encontrar el chunk a partir del pointer
    

    /// obtenemos el header del malloc, sabiendo que si tengo el puntero del malloc y le resto el tamaño del header obtengo la posicion del header 
    AllocationHeader *header = (AllocationHeader *)(((char *)ptr) - sizeof(AllocationHeader));

    // Obtener el encabezado del primer bloque de memoria para poder movernos
    MemoryChunkHeader *chunk = first_chunk;
    
    
    while(chunk!=NULL){
        //El puntero tiene que estar entre el puntero de address del chunk y la cantidad de unidades del mismo chunk
        if((ptr > chunk->addr) && (ptr < chunk->addr + (chunk->chunk_total_units * UNIT_SIZE))){ 
            printf("\n\n\nEncontre el chunk\n\n");
            break;
        }
        //no era este chunk me sigo moviendo en mi lista
        chunk = chunk->next;
        printf("\nPase de chunk\n");
    }


     // Calcular el índice de inicio en el bitmap basado en el AllocationHeader
    uint16_t start_byte_index = header->bit_index / 8;
    uint16_t start_bit_index = header->bit_index % 8;
    
    // Actualizar el contador de unidades disponibles en el chunk
    chunk->chunk_available_units += header->nunits;
    // Poner en cero los bits en el bitmap para representar el espacio como libre
    set_or_clear_bits(0,chunk->bitmap, start_byte_index, start_bit_index, header->nunits);
    //mostramos como queda el bitmap
    print_bitmap(chunk->bitmap, BITMAP_SIZE);
}

