#include "my_malloc_manager.h"

void *create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next)
{

    

    uint16_t contador_id = 0;

    MemoryChunkHeader* nuevo = mmap(NULL,  units_needed, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);\
    
    if (nuevo == MAP_FAILED) {
        //error(EXIT_FAILURE, errno, "Falló el mmap");
    }

    nuevo->id = contador_id;
    nuevo->chunk_total_units = UNITS_PER_CHUNK;
    nuevo->chunk_available_units = UNITS_PER_CHUNK;
    nuevo->is_large_allocation = is_large_allocation;
    nuevo->bitmap = (Bitmap)((char *)nuevo + sizeof(MemoryChunkHeader));
   //1 header, 1 bitmap
    nuevo->bitmap_size = BITMAP_SIZE;
    nuevo->next = next;
     for(int i=0;i<(uint16_t)(STRUCT_UNITS+sizeof(Bitmap) + (UNIT_SIZE - 1) / UNIT_SIZE);i++){
        first_fit(nuevo->bitmap,BITMAP_SIZE,1);
    }  
     

    printf("New chunk created, BITMAP pointer: %p\n", nuevo->bitmap);
    
    return nuevo;
}