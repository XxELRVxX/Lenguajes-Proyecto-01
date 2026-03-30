/**
 * @file cargar_guardar.h
 * @brief Definicion de funciones para cargar y guardar datos del sistema.
 */

#ifndef CARGAR_GUARDAR_H
#define CARGAR_GUARDAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "lista_sitios.h"
#include "lista_eventos.h"
#include "lista_facturas.h"


/**
 * @brief Guarda la lista de sitios en un archivo.
 * @param lista_sitios Puntero constante a la lista de sitios.
 * @param ruta Ruta del archivo donde guardar.
 * @return Codigo de exito o error.
 */
int guardar_sitios(const ListaSitios *lista_sitios, const char *ruta);

/**
 * @brief Guarda la lista de eventos en un archivo.
 * @param lista_eventos Puntero constante a la lista de eventos.
 * @param ruta Ruta del archivo donde guardar.
 * @return Codigo de exito o error.
 */
int guardar_eventos(const ListaEventos *lista_eventos, const char *ruta);

/**
 * @brief Guarda la lista de facturas en un archivo.
 * @param lista_facturas Puntero constante a la lista de facturas.
 * @param ruta Ruta del archivo donde guardar.
 * @return Codigo de exito o error.
 */
int guardar_facturas(const ListaFacturas *lista_facturas, const char *ruta);

/**
 * @brief Carga la lista de sitios desde un archivo.
 * @param lista_sitios Puntero a la lista de sitios.
 * @param ruta Ruta del archivo a cargar.
 * @return Codigo de exito o error.
 */
int cargar_sitios(ListaSitios *lista_sitios, const char *ruta);

/**
 * @brief Carga la lista de eventos desde un archivo.
 * @param lista_eventos Puntero a la lista de eventos.
 * @param lista_sitios Puntero constante a la lista de sitios.
 * @param ruta Ruta del archivo a cargar.
 * @return Codigo de exito o error.
 */
int cargar_eventos(ListaEventos *lista_eventos, const ListaSitios *lista_sitios, const char *ruta);

/**
 * @brief Carga la lista de facturas desde un archivo.
 * @param lista_facturas Puntero a la lista de facturas.
 * @param lista_eventos Puntero constante a la lista de eventos.
 * @param ruta Ruta del archivo a cargar.
 * @return Codigo de exito o error.
 */
int cargar_facturas(ListaFacturas *lista_facturas, const ListaEventos *lista_eventos, const char *ruta);


#endif //CARGAR_GUARDAR_H