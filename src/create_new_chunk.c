#include "my_malloc_manager.h"
int contador_chunks=0;
MemoryChunkHeader *first_chunk;
void *create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next) {
    size_t total_size = UNITS_PER_CHUNK;
    //UNITS_PER_CHUNK  
    void *ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    
    if (ptr == MAP_FAILED) {
        //tirame un print diciendo que exploto y no hagas un return null oka
        printf("Memory mapping failed");
        return NULL;
    }
    
    MemoryChunkHeader * chunk = (MemoryChunkHeader *)ptr;
    chunk->addr = ptr;
    chunk->id = contador_chunks++; //ID único, actualizado según corresponde
    chunk->is_large_allocation = is_large_allocation;
    chunk->chunk_total_units = units_needed;
    chunk->chunk_available_units = units_needed - (sizeof(MemoryChunkHeader) * 8 / UNIT_SIZE); // Ajustar por el tamaño del encabezado
    chunk->bitmap = (Bitmap)(chunk + 1); // Justo después del encabezado
    chunk->bitmap_size = BITMAP_SIZE;
    chunk->next = next;

    // Inicializar el bitmap a 0 manualmente
    if(!is_large_allocation){
        set_or_clear_bits(1, chunk->bitmap, 0, 0, STRUCT_UNITS + ((sizeof(BITMAP_SIZE) + UNIT_SIZE - 1) / UNIT_SIZE));
    }

    printf("New chunk created, BITMAP pointer: %p\n", chunk->bitmap);
    return chunk;
}