#include "my_malloc_manager.h"
int contador_chunks = 0;
MemoryChunkHeader *first_chunk;

void *create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next)
{   
    // UNITS_PER_CHUNK 
    uint16_t used_units = is_large_allocation ? STRUCT_UNITS : STRUCT_UNITS + BITMAP_UNITS;//paso el profe

    uint16_t total_units_to_mmap = is_large_allocation ? units_needed + STRUCT_UNITS : UNITS_PER_CHUNK;//paso el profe

    void *ptr = mmap(NULL, total_units_to_mmap, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0); //no paso

    if (ptr == MAP_FAILED)
    {
        // no funciono el mmap
        printf("Memory mapping failed");
        return NULL;
    }

    MemoryChunkHeader *chunk = (MemoryChunkHeader *)ptr;
    chunk->addr = ptr;
    chunk->id = contador_chunks++; // ID único, actualizado según corresponde lo usamos para fijarnos si es el primer chunk cuando libero
    chunk->is_large_allocation = is_large_allocation; 
    chunk->chunk_total_units = total_units_to_mmap;

    chunk->chunk_available_units =  total_units_to_mmap - used_units; // Ajustar por el tamaño del encabezado
    chunk->bitmap = is_large_allocation ? NULL : (Bitmap)ptr + (STRUCT_UNITS * UNIT_SIZE); // Se supone que está despues del header

    
    chunk->bitmap_size = is_large_allocation ? 0 : BITMAP_SIZE;
    chunk->next = next;

    // Inicializar el bitmap a 0 manualmente
    if (!is_large_allocation)
    {
        set_or_clear_bits(0, chunk->bitmap, 0, 0, UNITS_PER_CHUNK);
        set_or_clear_bits(1, chunk->bitmap, 0, 0, STRUCT_UNITS + BITMAP_UNITS);
        
    }
    
    printf("Se crea nuevo chunk");
    return chunk;
}