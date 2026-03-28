/**
 * @file sector.h
 * @brief Definicion de la estructura y funciones para el manejo de sectores.
 */

#ifndef SECTOR_H
#define SECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_asientos.h"

/**
 * @struct Sector
 * @brief Estructura que representa un sector de un sitio.
 */
typedef struct {
    char *nombre; /**< Nombre del sector */
    char inicial; /**< Inicial del sector */
    int cantidad_asientos; /**< Cantidad de asientos en el sector */
    ListaAsientos asientos; /**< Lista de asientos del sector */
} Sector;


/**
 * @brief Crea un sector con los datos proporcionados.
 * @param nombre_sector Nombre del sector.
 * @param cantidad Cantidad de asientos.
 * @param inicial Inicial del sector.
 * @return Sector inicializado.
 */
Sector crear_sector(const char *nombre_sector, int cantidad, char inicial);


/**
 * @brief Libera la memoria asociada a un sector.
 * @param sector Puntero al sector a liberar.
 */
void liberar_sector(Sector *sector);


/**
 * @brief Resetea el sector a su estado inicial.
 * @param sector Puntero al sector a resetear.
 */
void resetear_sector(Sector *sector);


/**
 * @brief Muestra la informacion del sector.
 * @param sector Puntero constante al sector.
 */
void mostrar_sector(const Sector *sector);


#endif //SECTOR_H