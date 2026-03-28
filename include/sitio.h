/**
 * @file sitio.h
 * @brief Definicion de la estructura y funciones para el manejo de sitios.
 */

#ifndef SITIO_H
#define SITIO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "lista_sectores.h"

/**
 * @struct Sitio
 * @brief Estructura que representa un sitio donde se realizan eventos.
 */
typedef struct {
    char *nombre; /**< Nombre del sitio */
    char *ubicacion; /**< Ubicacion del sitio */
    char *sitio_web; /**< Sitio web del lugar */
    ListaSectores lista_sectores; /**< Lista de sectores del sitio */
} Sitio;

/**
 * @brief Crea un sitio con los datos proporcionados.
 * @param nombre Nombre del sitio.
 * @param ubicacion Ubicacion del sitio.
 * @param sitio_web Sitio web del lugar.
 * @return Sitio inicializado.
 */
Sitio crear_sitio(const char *nombre, const char* ubicacion, const char *sitio_web);

/**
 * @brief Libera la memoria asociada a un sitio.
 * @param sitio Puntero al sitio a liberar.
 */
void liberar_sitio(Sitio *sitio);

/**
 * @brief Muestra la informacion del sitio.
 * @param sitio Puntero constante al sitio.
 */
void mostrar_sitio(const Sitio *sitio);

/**
 * @brief Cuenta la cantidad total de asientos en el sitio.
 * @param sitio Puntero constante al sitio.
 * @return Cantidad total de asientos.
 */
int contar_asientos_sitio(const Sitio *sitio);

#endif //SITIO_H