/**
 * @file lista_sitios.h
 * @brief Definicion de la estructura y funciones para el manejo de listas de sitios.
 */

#ifndef LISTA_SITIOS_H
#define LISTA_SITIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "sitio.h"

/**
 * @struct ListaSitios
 * @brief Estructura que representa una lista dinamica de sitios.
 */
typedef struct {
    Sitio *sitios; /**< Arreglo dinamico de sitios */
    int cantidad;  /**< Cantidad de sitios en la lista */
} ListaSitios;

/**
 * @brief Crea una lista de sitios vacia.
 * @return ListaSitios vacia.
 */
ListaSitios crear_lista_sitios();

/**
 * @brief Agrega un sitio a la lista.
 * @param lista_sitios Puntero a la lista de sitios.
 * @param nuevo_sitio Puntero al sitio a agregar.
 * @return Codigo de exito o error.
 */
int agregar_sitio(ListaSitios *lista_sitios, Sitio *nuevo_sitio);

/**
 * @brief Libera la memoria de la lista de sitios.
 * @param lista_sitios Puntero a la lista de sitios a liberar.
 */
void liberar_lista_sitios(ListaSitios *lista_sitios);

/**
 * @brief Busca un sitio por su nombre en la lista.
 * @param lista_sitios Puntero a la lista de sitios.
 * @param nombre_sitio Nombre del sitio a buscar.
 * @return Puntero al sitio encontrado o NULL.
 */
Sitio *buscar_sitio(ListaSitios *lista_sitios, const char* nombre_sitio);

/**
 * @brief Carga sitios desde un archivo.
 * @param lista_sitios Puntero a la lista de sitios.
 * @param ruta_archivo Ruta del archivo a cargar.
 * @return Numero de sitios cargados o error.
 */
int cargar_sitios(ListaSitios *lista_sitios, const char *ruta_archivo);

/**
 * @brief Muestra la informacion de todos los sitios de la lista.
 * @param lista_sitios Puntero constante a la lista de sitios.
 */
void mostrar_lista_sitios(const ListaSitios *lista_sitios);

#endif //LISTA_SITIOS_H