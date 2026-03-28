/**
 * @file lista_sectores.c
 * @brief Implementacio de las funciones para el manejo de listas de sectores.
 */

#include "lista_sectores.h"

/**
 * @brief Crea una lista de sectores vacia.
 * @return ListaSectores vacia.
 */
ListaSectores crear_lista_sectores() {
    ListaSectores lista;
    lista.cantidad_sectores = 0;
    lista.sectores = NULL;
    return lista;
}

/**
 * @brief Agrega un sector a la lista.
 * @param lista Puntero a la lista de sectores.
 * @param nuevo_sector Puntero al sector a agregar.
 * @return Codigo de exito o error.
 */
int agregar_sector(ListaSectores *lista, Sector *nuevo_sector) {
    if (buscar_sector(lista, nuevo_sector->nombre) != NULL) {
        liberar_sector(nuevo_sector);
        return OPERACION_FALLIDA_DUPLICADO;
    }

    Sector *temp_lista_sectores = realloc(lista->sectores, (lista->cantidad_sectores + 1) * sizeof(Sector));
    if (temp_lista_sectores == NULL) {
        liberar_sector(nuevo_sector);
        return OPERACION_FALLIDA_MEMORIA;
    }

    lista->sectores = temp_lista_sectores;
    lista->sectores[lista->cantidad_sectores] = *nuevo_sector;
    lista->cantidad_sectores++;

    return OPERACION_EXITOSA;
}

/**
 * @brief Libera la memoria de la lista de sectores.
 * @param lista Puntero a la lista de sectores a liberar.
 */
void liberar_lista_sectores(ListaSectores *lista) {
    for (int i = 0; i < lista->cantidad_sectores; i++) {
        liberar_sector(&lista->sectores[i]);
    }
    free(lista->sectores);
    lista->sectores = NULL;
    lista->cantidad_sectores = 0;
}

/**
 * @brief Busca un sector por su nombre en la lista.
 * @param lista Puntero a la lista de sectores.
 * @param nombre_sector Nombre del sector a buscar.
 * @return Puntero al sector encontrado o NULL.
 */
Sector *buscar_sector(ListaSectores *lista, const char *nombre_sector) {
    for (int i = 0; i < lista->cantidad_sectores; i++) {
        if (strcmp(lista->sectores[i].nombre, nombre_sector) == 0) {
            return &lista->sectores[i];
        }
    }
    return NULL;
}

/**
 * @brief Muestra la informacion de todos los sectores de la lista.
 * @param lista Puntero constante a la lista de sectores.
 */
void mostrar_lista_sectores(const ListaSectores *lista) {
    for (int i = 0; i < lista->cantidad_sectores; i++) {
        mostrar_sector(&lista->sectores[i]);
    }
}

/**
 * @brief Resetea la lista de sectores a su estado inicial.
 * @param lista Puntero a la lista de sectores a resetear.
 */
void resetear_lista_sectores(ListaSectores *lista) {
    for (int i = 0; i < lista->cantidad_sectores; i++) {
        resetear_sector(&lista->sectores[i]);
    }
}
