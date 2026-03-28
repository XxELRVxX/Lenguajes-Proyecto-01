/**
 * @file lista_sectores.h
 * @brief Definicion de la estructura y funciones para el manejo de listas de sectores.
 */

#ifndef LISTA_SECTORES_H
#define LISTA_SECTORES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sector.h"
#include "config.h"  

/**
 * @struct ListaSectores
 * @brief Estructura que representa una lista dinamica de sectores.
 */
typedef struct {
    int cantidad_sectores; /**< Cantidad de sectores en la lista */
    Sector *sectores;      /**< Arreglo dinamico de sectores */
} ListaSectores;


/**
 * @brief Crea una lista de sectores vacia.
 * @return ListaSectores vacia.
 */
ListaSectores crear_lista_sectores();

/**
 * @brief Agrega un sector a la lista.
 * @param lista Puntero a la lista de sectores.
 * @param nuevo_sector Puntero al sector a agregar.
 * @return Codigo de exito o error.
 */
int agregar_sector(ListaSectores *lista, Sector *nuevo_sector);

/**
 * @brief Libera la memoria de la lista de sectores.
 * @param lista Puntero a la lista de sectores a liberar.
 */
void liberar_lista_sectores(ListaSectores *lista);

/**
 * @brief Busca un sector por su nombre en la lista.
 * @param lista Puntero a la lista de sectores.
 * @param nombre_sector Nombre del sector a buscar.
 * @return Puntero al sector encontrado o NULL.
 */
Sector *buscar_sector(ListaSectores *lista, const char *nombre_sector);

/**
 * @brief Muestra la informacion de todos los sectores de la lista.
 * @param lista Puntero constante a la lista de sectores.
 */
void mostrar_lista_sectores(const ListaSectores *lista);


/**
 * @brief Resetea la lista de sectores a su estado inicial.
 * @param lista Puntero a la lista de sectores a resetear.
 */
void resetear_lista_sectores(ListaSectores *lista);

#endif
