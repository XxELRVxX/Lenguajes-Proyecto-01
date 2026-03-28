/**
 * @file lista_facturas.h
 * @brief Definicion de la estructura y funciones para el manejo de listas de facturas.
 */

#ifndef LISTA_FACTURAS_H
#define LISTA_FACTURAS_H


#include <stdio.h>
#include <stdlib.h>
#include "factura.h"

/**
 * @struct ListaFacturas
 * @brief Estructura que representa una lista dinamica de facturas.
 */
typedef struct {
    Factura *facturas; /**< Arreglo dinamico de facturas */
    int cantidad_facturas; /**< Cantidad de facturas en la lista */
} ListaFacturas;


/**
 * @brief Crea una lista de facturas vacia.
 * @return ListaFacturas vacia.
 */
 ListaFacturas crear_lista_facturas();

/**
 * @brief Busca una factura por su id en la lista.
 * @param lista Puntero constante a la lista de facturas.
 * @param id Identificador de la factura a buscar.
 * @return Puntero a la factura encontrada o NULL.
 */
 Factura *buscar_factura(const ListaFacturas *lista, int id);

/**
 * @brief Agrega una factura a la lista.
 * @param lista_facturas Puntero a la lista de facturas.
 * @param factura Puntero a la factura a agregar.
 * @return Codigo de exito o error.
 */
 int agregar_factura(ListaFacturas *lista_facturas, Factura *factura);

/**
 * @brief Muestra la informacion de todas las facturas de la lista.
 * @param lista_facturas Puntero constante a la lista de facturas.
 */
 void mostrar_lista_facturas(const ListaFacturas *lista_facturas);

/**
 * @brief Libera la memoria de la lista de facturas.
 * @param lista_facturas Puntero a la lista de facturas a liberar.
 */
 void liberar_lista_facturas(ListaFacturas *lista_facturas);

#endif // LISTA_FACTURAS_H
