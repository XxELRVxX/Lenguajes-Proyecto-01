/**
 * @file factura.h
 * @brief Definicion de la estructura y funciones para el manejo de facturas.
 */
#ifndef FACTURA_H
#define FACTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"
#include "fecha.h"
#include "config.h"
#include "lista_asientos.h"

/**
 * @struct FacturaDetalleAsiento
 * @brief Estructura que representa el detalle de un asiento en una factura.
 */
typedef struct {
    char *numero_asiento; /**< Numero identificador del asiento */
    float costo;          /**< Costo del asiento */
} FacturaDetalleAsiento;

/**
 * @struct Factura
 * @brief Estructura que representa una factura.
 */
typedef struct {
    int id; /**< Identificador unico de la factura */
    Fecha fecha_compra; /**< Fecha de la compra */
    char *cliente_cedula; /**< Cedula del cliente */
    char *cliente_nombre; /**< Nombre del cliente */
    Evento *evento; /**< Puntero al evento asociado */
    FacturaDetalleAsiento *asientos; /**< Detalle de asientos comprados */
    int cantidad_asientos; /**< Cantidad de asientos comprados */
    float subtotal; /**< Subtotal de la factura */
    float costo_servicio; /**< Costo de servicio aplicado */
    float total; /**< Total a pagar */
} Factura;


/**
 * @brief Crea una factura a partir de los datos proporcionados.
 * @param evento Puntero al evento.
 * @param fecha_compra Puntero a la fecha de compra.
 * @param cliente_cedula Cedula del cliente.
 * @param cliente_nombre Nombre del cliente.
 * @param asientos_comprados Puntero a la lista de asientos comprados.
 * @return Factura inicializada.
 */
Factura crear_factura(Evento *evento, const Fecha *fecha_compra,
                      const char *cliente_cedula, const char *cliente_nombre,
                      const ListaAsientos *asientos_comprados);

                      /**
 * @brief Muestra la informacion de la factura.
 * @param factura Puntero constante a la factura.
 */
void mostrar_factura(const Factura *factura);

/**
 * @brief Libera la memoria asociada a una factura.
 * @param factura Puntero a la factura a liberar.
 */
void liberar_factura(Factura *factura);

#endif // FACTURA_H
