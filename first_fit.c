#include "my_malloc_manager.h"

#define NULL_VALUE -1

void lista_decimal_a_binario(unsigned char *bitmap, int *lista_en_binario, size_t bitmap_size){

    for (int i = 0; i < bitmap_size; i++) {
        for (int j = 7; j >= 0; j--) {
            lista_en_binario[(i * 8) + j] = *bitmap & 1;
            *bitmap >>= 1;
        }
    }

}

void lista_binario_a_decimal(unsigned char *bitmap, int *lista_en_binario, size_t bitmap_size){

    for (int i = 0; i < bitmap_size; i++) {
        unsigned char decimal = 0;
        for (int j = 0; j < 8; j++) {
            decimal <<= 1;
            decimal |= lista_en_binario[(i * 8) + j];
        }
        bitmap[i] = decimal;
    }

}

// Esta función busca un hueco de tamaño units_needed en el bitmap.
int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed) {
    int bitmap_en_binario[bitmap_size * 8];

    lista_decimal_a_binario(bitmap, bitmap_en_binario, bitmap_size);

    int huecos_encontrados = 0;
    int indice_inicio_hueco = NULL_VALUE;
    int indice_final_hueco = NULL_VALUE;

    for(int i = 0; i < bitmap_size * 8; i++){
        // Se encontró un hueco
        if(bitmap_en_binario[i] == 0){

            // Inicializo el inicio del hueco
            if(indice_inicio_hueco == NULL_VALUE){
                indice_inicio_hueco = i;
            }
            
            // Voy agrandando el final del hueco
            indice_final_hueco = indice_final_hueco != NULL_VALUE ? indice_final_hueco + 1 : i;

            // Voy sumando huecos
            huecos_encontrados++;
            
            // Si llegue a encontrar el hueco entero activo el freno de mano
            if (huecos_encontrados == units_needed){
                break;
            }
        
        // Si estaba encontrando hueco pero no le da el tamaño reinicio las variables
        }else if(indice_inicio_hueco != NULL_VALUE){
            indice_inicio_hueco = NULL_VALUE;
            indice_final_hueco = NULL_VALUE;
            huecos_encontrados = 0;
        }
    }

    /* printf("Units_needed: %li\n", units_needed);
    printf("Inicio hueco: %i\n", indice_inicio_hueco);
    printf("Final hueco: %i\n", indice_final_hueco); */

    for (int i = indice_inicio_hueco; i < indice_final_hueco + 1; i++){
        bitmap_en_binario[i] = 1;
    }

    lista_binario_a_decimal(bitmap, bitmap_en_binario, bitmap_size);
    
   /*  printf("Resultado en binario: ");
    for (int i = 0; i < bitmap_size * 8; i++){
        if ( i % 8 == 0 && i != 0){
            printf(" ");
        }
        printf("%i", bitmap_en_binario[i]);
    }

    printf("\n");

    printf("Resultado en decimal: ");

    for (int i = 0; i < bitmap_size; i++){
        printf("%i: (%i) ", i, bitmap[i]);
    }
    
    printf("\n"); */
    return 0;
}