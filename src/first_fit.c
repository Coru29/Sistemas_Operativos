#include "my_malloc_manager.h"

#define NULL_VALUE -1

// Esta función busca un hueco de tamaño units_needed en el bitmap.
int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed)
{
    char bitmap_en_binario[bitmap_size * 8];

    // Paso la lista de decimal a binario para trabajar mas facil
    lista_decimal_a_binario(bitmap, bitmap_en_binario, bitmap_size);

    /* --------------------------------------------------------------------- */
    int indice_inicio_hueco = NULL_VALUE;
    size_t huecos_encontrados = 0;

    for (size_t i = 0; i < bitmap_size * 8; i++)
    {
        // Se encontró un hueco
        if (bitmap_en_binario[i] == 0)
        {

            // Inicializo el inicio del hueco
            if (indice_inicio_hueco == NULL_VALUE)
            {
                indice_inicio_hueco = i;
            }

            // Voy sumando huecos
            huecos_encontrados++;

            // Si llegue a encontrar el hueco entero activo el freno de mano
            if (huecos_encontrados == units_needed)
            {
                break;
            }
        }
        // Si estaba encontrando hueco pero no le da el tamaño reinicio las variables
        else if (indice_inicio_hueco != NULL_VALUE)
        {
            indice_inicio_hueco = NULL_VALUE;
            huecos_encontrados = 0;
        }
    }
    /* --------------------------------------------------------------------- */

    /* Ocupo con 1s las unidades */
    if (huecos_encontrados == units_needed)
    {
        for (size_t i = indice_inicio_hueco; i < indice_inicio_hueco + units_needed; i++)
        {
            bitmap_en_binario[i] = 1;
        }
    }
    // Si no encontro lugar, reseteo las vars.
    else
    {
        indice_inicio_hueco = NULL_VALUE;
    }

    // Paso la lista de binario a decimal y lo mando al bitmap
    lista_binario_a_decimal(bitmap, bitmap_en_binario, bitmap_size);

    return indice_inicio_hueco;
}