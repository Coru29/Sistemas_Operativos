#include "my_malloc_manager.h"


int contador_id = 0;

void *create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next){
    Bitmap nuevo_bitmap[BITMAP_SIZE];

    MemoryChunkHeader nuevo;
    nuevo.id = contador_id++;
    nuevo.chunk_total_units = UNITS_PER_CHUNK;
    nuevo.chunk_available_units =  UNITS_PER_CHUNK;
    nuevo.is_large_allocation = is_large_allocation;
    nuevo.bitmap = nuevo_bitmap;
    nuevo.bitmap_size = BITMAP_SIZE;
    nuevo.next = NULL;
    
    *next->next = nuevo;
}