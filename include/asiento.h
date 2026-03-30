/**
 * @file asiento.h
 * @brief Definición de la estructura y funciones para el manejo de asientos.
 */

#ifndef ASIENTO_H
#define ASIENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

/**
 * @struct Asiento
 * @brief Representa un asiento con su numero y estado.
 */
typedef struct {
    char *numero_asiento; /**< Numero identificador del asiento. */
    int estado;           /**< Estado del asiento. 0 = disponbile y 1 = vendido. */
} Asiento;

/**
 * @brief Crea un nuevo asiento.
 * @param numero_asiento Numero identificador del asiento.
 * @return Estructura Asiento inicializada.
 */
Asiento crear_asiento(const char *numero_asiento);

/**
 * @brief Libera la memoria asociada a un asiento.
 * @param asiento Puntero al asiento que hay que liberar su memoria.
 */
void liberar_asiento(Asiento *asiento);

/**
 * @brief Marca un asiento como vendido.
 * @param asiento Puntero al asiento que se va a vender.
 * @return Codigo de exito o fallo.
 */
int vender_asiento(Asiento *asiento);

/**
 * @brief Marca un asiento como disponible.
 * @param asiento Puntero al asiento que se va a desocupar.
 */
void desocupar_asiento(Asiento *asiento);

/**
 * @brief Muestra la información de un asiento.
 * @param asiento Puntero constante al asiento.
 */
void informacion_asiento(const Asiento *asiento);

#endif // ASIENTO_H