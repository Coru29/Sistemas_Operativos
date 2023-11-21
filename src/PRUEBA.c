#include "my_malloc_manager.h"
#include <assert.h>

int main() {
    // Test de create_new_chunk
    printf("Testing create_new_chunk...\n");
    MemoryChunkHeader *chunk = create_new_chunk(UNITS_PER_CHUNK, 0, NULL);
    assert(chunk != NULL);
    printf("create_new_chunk passed.\n");

    // Test de first_fit
    printf("Testing first_fit...\n");
    int fit_index = first_fit(chunk->bitmap, chunk->bitmap_size, 5);
    assert(fit_index != -1);
    printf("first_fit passed with fit_index = %d.\n", fit_index);

    // Test de print_bitmap
    printf("Testing print_bitmap...\n");
    print_bitmap(chunk->bitmap, chunk->bitmap_size);

    // Test de my_malloc y my_free
    printf("Testing my_malloc and my_free...\n");
    void *allocated_memory = my_malloc(64); // Solicitar 64 bytes
    assert(allocated_memory != NULL);
    printf("my_malloc passed.\n");
    print_bitmap(chunk->bitmap, chunk->bitmap_size);

    my_free(allocated_memory);
    printf("my_free passed.\n");
    print_bitmap(chunk->bitmap, chunk->bitmap_size);

    // Limpiar
    munmap(chunk, sizeof(MemoryChunkHeader) + BITMAP_SIZE);

    printf("All tests passed.\n");
    return 0;
}
