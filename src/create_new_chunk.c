#include "my_malloc_manager.h"



void *create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next){
    
    Bitmap nuevo_bitmap[BITMAP_SIZE] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    uint16_t contador_id = 0;

    MemoryChunkHeader *nuevo = NULL;

    nuevo->id = contador_id;
    nuevo->chunk_total_units = UNITS_PER_CHUNK;
    nuevo->chunk_available_units =  UNITS_PER_CHUNK;
    nuevo->is_large_allocation = is_large_allocation;
    //nuevo->bitmap = *nuevo_bitmap;
    nuevo->bitmap_size = BITMAP_SIZE;
    nuevo->next = NULL;

    if (next == NULL) {
        // Si no hay chunks, este es el primer chunk
        /* next = nuevo; */
    } else {
        // Si ya hay chunks, navegar hasta el final de la lista y añadir el nuevo chunk allí
        /* MemoryChunkHeader *current = next;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = nuevo; */
    }

    return nuevo;
}