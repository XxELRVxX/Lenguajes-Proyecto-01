/**
 * @file asiento.c
 * @brief Implementación de las funciones para el manejo de asientos.
 */

#include "asiento.h"

/**
 * @brief Crea un nuevo asiento.
 * @param numero_asiento Numero identificador del asiento.
 * @return Estructura Asiento inicializada.
 */
Asiento crear_asiento(const char *numero_asiento) {
    Asiento asiento;
    asiento.numero_asiento = malloc(strlen(numero_asiento) + 1);
    strcpy(asiento.numero_asiento,numero_asiento);
    asiento.estado = ASIENTO_DISPONIBLE;
    return asiento;
}    

/**
 * @brief Libera la memoria asociada a un asiento.
 * @param asiento Puntero al asiento que hay que liberar su memoria.
 */
void liberar_asiento(Asiento *asiento) {
    if(asiento->numero_asiento) {
        free(asiento->numero_asiento);
        asiento->numero_asiento = NULL;
    }
}


/**
 * @brief Marca un asiento como vendido.
 * @param asiento Puntero al asiento que se va a vender.
 * @return Codigo de exito o fallo.
 */
int vender_asiento(Asiento *asiento) {
    if (asiento->estado == ASIENTO_DISPONIBLE) {
        asiento->estado = ASIENTO_VENDIDO;
        return OPERACION_EXITOSA;
    }
    return OPERACION_FALLIDA; 
}

/**
 * @brief Marca un asiento como disponible.
 * @param asiento Puntero al asiento que se va a desocupar.
 */
void desocupar_asiento(Asiento *asiento) {
    asiento->estado = ASIENTO_DISPONIBLE;
}

/**
 * @brief Muestra la información de un asiento.
 * @param asiento Puntero constante al asiento.
 */
void informacion_asiento(const Asiento *asiento) {
    printf("    %s ",asiento->numero_asiento);
    if (asiento->estado == ASIENTO_DISPONIBLE) {
        printf("[Disponible] \n");
    } else {
        printf("[Vendido] \n");
    }
}