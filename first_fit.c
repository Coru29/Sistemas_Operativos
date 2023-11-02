#include "my_malloc_manager.h"

#define NULL_VALUE -1

void lista_decimal_a_binario(unsigned char *bitmap, char *lista_en_binario, size_t bitmap_size)
{

    printf("lista_decimal_a_binario -> ");
    for (int i = 0; i < bitmap_size; i++)
    {
        char byte_binario [8];
        int indice = 8;

        

        while (bitmap[i] > 0)
        {
            byte_binario[indice] = bitmap[i] % 2;
            bitmap[i] /= 2;
            indice--;
        }

        
        for (size_t j = 0; j < 8; j++)
        {   
            printf("%i",  byte_binario[j]);
            lista_en_binario[(i * 8) + j] = byte_binario[j];
        }
        printf(" ");
    }
    printf("\n");
}

void lista_binario_a_decimal(unsigned char *bitmap, char *lista_en_binario, size_t bitmap_size)
{

    for (int i = 0; i < bitmap_size; i++)
    {
        unsigned char decimal = 0;
        for (int j = 0; j < 8; j++)
        {
            decimal <<= 1;
            decimal |= lista_en_binario[(i * 8) + j];
        }
        bitmap[i] = decimal;
    }
}

// Esta función busca un hueco de tamaño units_needed en el bitmap.
int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed)
{
    char bitmap_en_binario[bitmap_size*8];

    printf("Llega en decimal: ");

    for (int i = 0; i < bitmap_size; i++){
        printf("%i ", bitmap[i]);
    }

    printf("\n");   
    lista_decimal_a_binario(bitmap, bitmap_en_binario, bitmap_size);

    /* --------------------------------------------------------------------- */

    int indice_inicio_hueco = NULL_VALUE;
    int indice_final_hueco = NULL_VALUE;
    int huecos_encontrados = 0;

    for (int i = 0; i < bitmap_size * 8; i++)
    {
        // Se encontró un hueco
        if (bitmap_en_binario[i] == 0)
        {

            // Inicializo el inicio del hueco
            if (indice_inicio_hueco == NULL_VALUE)
            {
                indice_inicio_hueco = i;
            }

            // Voy agrandando el final del hueco
            indice_final_hueco = i;

            // Voy sumando huecos
            huecos_encontrados++;

            // Si llegue a encontrar el hueco entero activo el freno de mano
            if (huecos_encontrados == units_needed)
            {
                break;
            }

            // Si estaba encontrando hueco pero no le da el tamaño reinicio las variables
        }
        else if (indice_inicio_hueco != NULL_VALUE)
        {
            indice_inicio_hueco = NULL_VALUE;
            indice_final_hueco = NULL_VALUE;
            huecos_encontrados = 0;
        }
    }
    /* --------------------------------------------------------------------- */

    /* LLENO LOS 1 */
    for (int i = indice_inicio_hueco; i < indice_inicio_hueco + units_needed; i++)
    {
        bitmap_en_binario[i] = 1;
    }

    printf("Resultado en bianrio: ");

    for (int i = 0; i < 8 * bitmap_size; i++){
        if (i % 8 == 0 && i != 0){
            printf(" ");
        }
        
        printf("%i", bitmap_en_binario[i]);
    }
    printf("\n");

    printf("Inicio: %i, Fin: %li \n", indice_inicio_hueco, indice_inicio_hueco + units_needed);

    lista_binario_a_decimal(bitmap, bitmap_en_binario, bitmap_size);

    printf("Resultado en decimal: ");

    for (int i = 0; i < bitmap_size; i++){
        printf("%i: (%i) ", i, bitmap[i]);
    }

    return indice_inicio_hueco;
}