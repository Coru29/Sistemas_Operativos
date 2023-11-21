#include "my_malloc_manager.h"
#include <stdio.h>

int main() {
    void *allocated_memory;
    size_t size;
    char command;
    int exit = 0;

    printf("Gestor de memoria personalizado\n");
    printf("Comandos:\n");
    printf("  a <tamaño> - Asignar memoria\n");
    printf("  f <dirección> - Liberar memoria\n");
    printf("  q - Salir\n");

    while (!exit) {
        printf("Ingrese comando: ");
        scanf(" %c", &command);

        switch (command) {
            case 'a':
                printf("Ingrese tamaño de memoria para asignar: ");
                scanf("%zu", &size);
                allocated_memory = my_malloc(size);
                if (allocated_memory != NULL) {
                    printf("Memoria asignada en dirección: %p\n", allocated_memory);
                } else {
                    printf("Error al asignar memoria\n");
                }
                break;

            case 'f':
                printf("Ingrese dirección de memoria para liberar (formato hexadecimal): ");
                scanf("%p", &allocated_memory);
                my_free(allocated_memory);
                printf("Memoria liberada\n");
                break;

            case 'q':
                exit = 1;
                break;

            default:
                printf("Comando no reconocido\n");
        }
    }

    printf("Saliendo del programa...\n");
    return 0;
}
