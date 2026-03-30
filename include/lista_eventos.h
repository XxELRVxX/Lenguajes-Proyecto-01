/**
 * @file lista_eventos.h
 * @brief Definicion de la estructura y funciones para el manejo de listas de eventos.
 */

#ifndef LISTA_EVENTOS_H
#define LISTA_EVENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"


/**
 * @struct ListaEventos
 * @brief Estructura que representa una lista dinamica de eventos.
 */
typedef struct {
    Evento *eventos; /**< Arreglo dinamico de eventos */
    int cantidad_eventos; /**< Cantidad de eventos en la lista */
} ListaEventos;


/**
 * @brief Crea una lista de eventos vacia.
 * @return ListaEventos vacia.
 */
ListaEventos crear_lista_eventos();

/**
 * @brief Agrega un evento a la lista.
 * @param lista_eventos Puntero a la lista de eventos.
 * @param nuevo_evento Puntero al evento a agregar.
 * @return Codigo de exito o error.
 */
int agregar_evento(ListaEventos *lista_eventos, Evento *nuevo_evento);

/**
 * @brief Busca un evento por su nombre en la lista.
 * @param lista_eventos Puntero a la lista de eventos.
 * @param nombre_evento Nombre del evento a buscar.
 * @return Puntero al evento encontrado o NULL.
 */
Evento *buscar_evento(ListaEventos *lista_eventos, const char *nombre_evento);

/**
 * @brief Muestra la informacion de todos los eventos de la lista.
 * @param lista_eventos Puntero constante a la lista de eventos.
 */
void mostrar_lista_eventos(const ListaEventos *lista_eventos);

/**
 * @brief Libera la memoria de la lista de eventos.
 * @param lista_eventos Puntero a la lista de eventos a liberar.
 */
void liberar_lista_eventos(ListaEventos *lista_eventos);

#endif //LISTA_EVENTOS_H