#include "my_malloc_manager.h"
int contador_chunks=0;
MemoryChunkHeader *first_chunk;
void *create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next) {
    //UNITS_PER_CHUNK  
    void *ptr = mmap(NULL, units_needed, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    
    if (ptr == MAP_FAILED) {
        //no funciono el mmap
        printf("Memory mapping failed");
        return NULL;
    }
    
    MemoryChunkHeader * chunk = (MemoryChunkHeader *)ptr;
    chunk->addr = ptr;
    chunk->id = contador_chunks++; //ID único, actualizado según corresponde lo usamos para fijarnos si es el primer chunk cuando libero  
    chunk->is_large_allocation = is_large_allocation; //no llegamos a implementar esto
    chunk->chunk_total_units = UNITS_PER_CHUNK;
    chunk->chunk_available_units = UNITS_PER_CHUNK - (sizeof(MemoryChunkHeader) / UNIT_SIZE)-2; // Ajustar por el tamaño del encabezado
    chunk->bitmap = (Bitmap)((void*)chunk + sizeof(MemoryChunkHeader)); // Se supone que está despues del header
    chunk->bitmap_size = BITMAP_SIZE;
    chunk->next = next;

    // Inicializar el bitmap a 0 manualmente
    if(!is_large_allocation){
        set_or_clear_bits(1, chunk->bitmap, 0, 0, STRUCT_UNITS + ((sizeof(BITMAP_SIZE) + UNIT_SIZE - 1) / UNIT_SIZE));
    }

    printf("Se crea nuevo chunk");
    return chunk;
}