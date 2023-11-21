#include "my_malloc_manager.h"

void my_free(void *ptr) {
    int id_a_sacar=-1;
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
    //mostramos como queda el bitmap del chunk
    print_bitmap(chunk->bitmap, BITMAP_SIZE);
    if((chunk->chunk_available_units==chunk->chunk_total_units-(sizeof(MemoryChunkHeader) * 8 / UNIT_SIZE))&&(chunk->id!=0)){  //tengo que sacar este chunk esta vacio
        id_a_sacar=chunk->id;
    }
    if(id_a_sacar!=-1){
        MemoryChunkHeader *chunk2 = first_chunk;
        while(chunk2!=NULL){
            if(chunk2->next->id==id_a_sacar){
                chunk2->next=chunk2->next->next;
            }
            chunk2 = chunk2->next;
        }
    printf("Se borro el chunk.\n");
    }
}

