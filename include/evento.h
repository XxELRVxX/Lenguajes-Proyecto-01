/**
 * @file evento.h
 * @brief Definicion de la estructura y funciones para el manejo de eventos.
 */

#ifndef EVENTO_H
#define EVENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fecha.h"
#include "sitio.h"

/**
 * @struct Evento
 * @brief Estructura que representa un evento.
 */
typedef struct {
    char *nombre_evento;
    char *productora;
    Fecha fecha;
    Sitio *sitio;
    float *montos_por_sector;
    int cantidad_sectores;
    ListaAsientos *asientos_por_sector;
}Evento;

/**
 * @brief Crea un evento.
 * @param nombre_evento Nombre del evento.
 * @param productora Productora del evento.
 * @param fecha Fecha del evento.
 * @param sitio Puntero al sitio donde se realiza el evento.
 * @return Evento inicializado.
 */
Evento crear_evento(const char *nombre_evento, const char* productora,
     Fecha fecha, Sitio *sitio);

/**
 * @brief Libera la memoria asociada a un evento.
 * @param evento Puntero al evento a liberar.
 */
void liberar_evento(Evento *evento);

/**
 * @brief Muestra el estado del evento.
 * @param evento Puntero constante al evento.
 */
void estado_evento(const Evento *evento);

/**
 * @brief Muestra la informacion del evento.
 * @param evento Puntero constante al evento.
 */
void mostrar_evento(const Evento *evento);



/**
 * @brief Asigna el monto a un sector especifico del evento.
 * @param evento Puntero al evento.
 * @param sector Puntero al sector.
 * @param monto Monto a asignar.
 */
void asignar_monto_sector(Evento *evento, Sector *sector, float monto);

/**
 * @brief Obtiene el precio de un asiento segun el sector.
 * @param evento Puntero constante al evento.
 * @param asiento Puntero constante al asiento.
 * @return Precio del asiento.
 */
float obtener_precio_asiento(const Evento *evento, const Asiento *asiento);



#endif //EVENTO_H