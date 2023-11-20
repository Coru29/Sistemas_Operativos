#include "my_malloc_manager.h"

static ;

void *malloc(size_t nbytes)
{
    // hay que pasar los bytes a unidades
    MemoryChunkHeader *mem = create_new_chunk(UNITS_PER_CHUNK * UNIT_SIZE, 0, NULL);
    int unidades = (nbytes + UNIT_SIZE - 1) / UNIT_SIZE;

    if (mem == NULL)
    {
        mem = create_new_chunk(UNITS_PER_CHUNK * UNIT_SIZE, 0, NULL);
    }

    /* while (mem->next != NULL)
    {
        if (first_fit(mem->bitmap, BITMAP_SIZE, cantidad_a_poner) == -1)
        {
            mem = mem->next;
        }
        else
        {
            first_fit(mem->bitmap, BITMAP_SIZE, cantidad_a_poner);
            break;
        }
    } */
    int resultado_first_fit = first_fit(mem->bitmap, BITMAP_SIZE, 10);
    if (resultado_first_fit == -1){
        mem = create_new_chunk(UNITS_PER_CHUNK * UNIT_SIZE, 0, mem);
        resultado_first_fit = first_fit(mem->bitmap, BITMAP_SIZE, 10);
    }
    //int resultado = first_fit(mem->bitmap,BITMAP_SIZE,unidades);
    return resultado_first_fit*UNIT_SIZE+mem;
}
// muy duroo
