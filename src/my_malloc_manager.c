#include "my_malloc_manager.h"

int main() {
    // Definiendo el bitmap.
    // Este array va a tener elementos que pueden ir de 0 a 255,
    // esto es genial para representar el bitmap, ya que la representacion 
    // binaria de cada elemento tiene 8 bits.
    unsigned char bitmap[BITMAP_SIZE];

    // Inicializar el bitmap con ceros.
    for (size_t i = 0; i < BITMAP_SIZE; i++) {
        bitmap[i] = 0;
    }

    // Imprimir el bitmap.
    printf("Bitmap inicial: ");
    print_bitmap(bitmap, BITMAP_SIZE);

    // Hacer varias invocaciones de first_fit y mostrar el resultado.
    int indices[] = {5, 10, 7, 20, 50, 2};  // Ejemplo de tamaños solicitados
    for (long unsigned int i = 0; i < sizeof(indices) / sizeof(indices[0]); i++) {
        int result = first_fit(bitmap, BITMAP_SIZE, indices[i]);
        if (result != -1) {
            printf("Alojados %d bits en el índice: %d\n", indices[i], result);
        } else {
            printf("No hay suficiente espacio para %d bits.\n", indices[i]);
        }
        print_bitmap(bitmap, BITMAP_SIZE);
    }

    printf("\n\nPruebas clear_bits \n\n");

    clear_bits(bitmap, 1, 2, 16);

    print_bitmap(bitmap, BITMAP_SIZE);

    printf("\n\nPruebas first_fit \n\n");

    first_fit(bitmap, BITMAP_SIZE, 17);

    print_bitmap(bitmap, BITMAP_SIZE);

    return 0;
}