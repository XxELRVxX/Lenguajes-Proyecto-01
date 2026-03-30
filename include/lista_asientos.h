/**
 * @file lista_asientos.h
 * @brief Definición de la estructura y funciones para el manejo de listas de asientos.
 */

#ifndef LISTA_ASIENTOS_H
#define LISTA_ASIENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asiento.h"
#include "config.h"

/**
 * @struct ListaAsientos
 * @brief Estructura que representa una lista dinamica de asientos.
 */
typedef struct {
    int cantidad_asientos; /**< Cantidad de asientos en la lista */
    Asiento *asientos;     /**< Puntero al inicio del arreglo dinámico de asientos */
}ListaAsientos;



/**
 * @brief Crea una lista de asientos con una cantidad y letra inicial.
 * @param cantidad Número de asientos que hay que crear.
 * @param inicial Letra inicial para los asientos.
 * @return ListaAsientos inicializada.
 */
ListaAsientos crear_lista_asientos(int cantidad, char inicial);

/**
 * @brief Crea una lista de asientos vacía.
 * @return ListaAsientos vacía.
 */
ListaAsientos crear_lista_asientos_vacia();

/**
 * @brief Agrega un asiento a la lista de forma dinamica.
 * @param lista_asientos Puntero a la lista de asientos.
 * @param asiento Puntero al asiento que se va a agregar.
 * @return Código de exito o error.
 */
int agregar_asiento_a_lista(ListaAsientos *lista, Asiento *asiento);

/**
 * @brief Libera la memoria de la lista de asientos.
 * @param lista_asientos Puntero a la lista de asientos por liberar.
 */
void liberar_lista_asientos(ListaAsientos *lista_asientos);


/**
 * @brief Resetea la lista de asientos a estado inicial.
 * @param lista_asientos Puntero a la lista de asientos a resetear.
 */
void resetear_lista_asientos(ListaAsientos *lista_asientos);

/**
 * @brief Muestra la informacion de todos los asientos de la lista.
 * @param lista_asientos Puntero constante a la lista a mostrar.
 */
void mostrar_lista_asientos(const ListaAsientos *lista_asientos);

/**
 * @brief Busca un asiento por su numero en la lista.
 * @param lista_asientos Puntero a la lista de asientos.
 * @param numero_asiento Numero identificador del asiento.
 * @return Puntero al asiento encontrado o NULL.
 */
Asiento *buscar_asiento(ListaAsientos *lista_asientos, const char *numero_asiento);

/**
 * @brief Obtiene un asiento por su indice en la lista.
 * @param lista_asientos Puntero constante a la lista.
 * @param indice Posicion del asiento en la lista.
 * @return Puntero al asiento correspondiente o NULL si el indice no es valido.
 */
Asiento *obtener_asiento(const ListaAsientos *lista_asientos, int indice);

/**
 * @brief Cuenta la cantidad de asientos disponibles en la lista.
 * @param lista_asientos Puntero constante a la lista.
 * @return Numero de asientos disponibles.
 */
int contar_asientos_disponibles(const ListaAsientos *lista_asientos);

/**
 * @brief Crea una copia de la lista de asientos.
 * @param lista_original Puntero constante a la lista original.
 * @return Copia de la lista de asientos.
 */
ListaAsientos copiar_lista_asientos(const ListaAsientos *lista_original);


#endif //LISTA_ASIENTOS_H