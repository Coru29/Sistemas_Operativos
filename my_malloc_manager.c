#include "my_malloc_manager.h"

int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed);

// Esta función imprime el bitmap en el formato solicitado.
void print_bitmap(unsigned char *bitmap, size_t bitmap_size) {
    for (size_t i = 0; i < bitmap_size; i++) {
        for (size_t j = 0; j < 8; j++) {
            printf("%d", (bitmap[i] >> (7 - j)) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    // 1. Definir el bitmap.
    char bitmap [BITMAP_SIZE][8];

    // 2. Inicializar el bitmap con ceros.
    for (size_t i = 0; i < BITMAP_SIZE; i++) {
        //bitmap[i] = {0, 0, 0, 0, 0, 0, 0};
        for (size_t j = 0; j < 8; j++)
        {
            bitmap[i][j] = 0;
        }
        
    }

    // 3. Imprimir el bitmap.
    //printf("Bitmap inicial: ");
    //print_bitmap(bitmap, BITMAP_SIZE);

    first_fit((unsigned char *)bitmap, BITMAP_SIZE, 10);
    // 4. Hacer varias invocaciones de first_fit y mostrar el resultado.
    int indices[] = {5, 10, 7, 20, 50, 2};  // Ejemplo de tamaños solicitados
    for (int i = 0; i < sizeof(indices) / sizeof(indices[0]); i++) {
        //int result = first_fit(bitmap, BITMAP_SIZE, indices[i]);
        //if (result != -1) {
            //printf("Alojados %d bits en el índice: %d\n", indices[i], result);
        //} else {
            //printf("No hay suficiente espacio para %d bits.\n", indices[i]);
        //}
        //print_bitmap(bitmap, BITMAP_SIZE);
    }

    return 0;
}

