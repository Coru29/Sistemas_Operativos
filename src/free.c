#include "my_malloc_manager.h"

void my_free(void *ptr) {
    if (!ptr) {
        // Si el ptr es NULL, no hacer nada
        return;
    }
    //necesitamos encontrar el chunk a partir del pointer
    

    /// Obtenga el encabezado de la asignación 
    AllocationHeader *header = (AllocationHeader *)(((char *)ptr) - sizeof(AllocationHeader));

    // Obtener el encabezado del bloque de memoria
    MemoryChunkHeader *chunk = first_chunk;// = (MemoryChunkHeader *)(((char *)header) - header->bit_index * UNIT_SIZE);
    
    
    while(chunk!=NULL){
        printf("\nQUE ONDA LOCO\n");
        if((ptr > chunk->addr) && (ptr < chunk->addr + (chunk->chunk_total_units * UNIT_SIZE))){
            printf("\n\n\nACA LOCCOOOOO\n\n");
            break;
        }
        chunk = chunk->next;
    }


     // Calcular el índice de inicio en el bitmap basado en el AllocationHeader
    uint16_t start_byte_index = header->bit_index / 8;
    uint16_t start_bit_index = header->bit_index % 8;
    
    // Actualizar el contador de unidades disponibles en el chunk
    chunk->chunk_available_units += header->nunits;
    // Limpiar los bits en el bitmap para marcar el espacio como libre
    set_or_clear_bits(0,chunk->bitmap, start_byte_index, start_bit_index, header->nunits);

    print_bitmap(chunk->bitmap, BITMAP_SIZE);
}

