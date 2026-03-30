/**
 * @file lista_eventos.c
 * @brief Implementación de las funciones para el manejo de listas de eventos.
 */
#include "lista_eventos.h"

/**
 * @brief Crea una lista de eventos vacia.
 * @return ListaEventos vacia.
 */
ListaEventos crear_lista_eventos() {
    ListaEventos lista;
    lista.eventos = NULL;
    lista.cantidad_eventos = 0;
    return lista;
}

/**
 * @brief Agrega un evento a la lista.
 * @param lista_eventos Puntero a la lista de eventos.
 * @param nuevo_evento Puntero al evento a agregar.
 * @return Codigo de exito o error.
 */
int agregar_evento(ListaEventos *lista_eventos, Evento *nuevo_evento) {
    if (buscar_evento(lista_eventos, nuevo_evento->nombre_evento) != NULL) {
        liberar_evento(nuevo_evento);
        return OPERACION_FALLIDA_DUPLICADO;
    }

    Evento *temp_lista_eventos = realloc(lista_eventos->eventos, (lista_eventos->cantidad_eventos + 1) * sizeof(Evento));
    if (temp_lista_eventos == NULL) {
        return OPERACION_FALLIDA_MEMORIA;
    }
    lista_eventos->eventos = temp_lista_eventos;
    lista_eventos->eventos[lista_eventos->cantidad_eventos] = *nuevo_evento;
    lista_eventos->cantidad_eventos++;
    return OPERACION_EXITOSA;
}

/**
 * @brief Busca un evento por su nombre en la lista.
 * @param lista_eventos Puntero a la lista de eventos.
 * @param nombre_evento Nombre del evento a buscar.
 * @return Puntero al evento encontrado o NULL.
 */
Evento *buscar_evento(ListaEventos *lista_eventos, const char *nombre_evento) {
    for (int i = 0; i<lista_eventos->cantidad_eventos; i++) {
        if (strcmp(lista_eventos->eventos[i].nombre_evento, nombre_evento) == 0) {
            return &lista_eventos->eventos[i];
        }
    }
    return NULL;
}

/**
 * @brief Muestra la informacion de todos los eventos de la lista.
 * @param lista_eventos Puntero constante a la lista de eventos.
 */
void mostrar_lista_eventos(const ListaEventos *lista) {
    printf("Lista de eventos:\n");
    for (int i = 0; i < lista->cantidad_eventos; i++) {
        mostrar_evento(&lista->eventos[i]);
    }
}

/**
 * @brief Libera la memoria de la lista de eventos.
 * @param lista_eventos Puntero a la lista de eventos a liberar.
 */
void liberar_lista_eventos(ListaEventos *lista_eventos) {
    for (int i = 0; i<lista_eventos->cantidad_eventos; i++) {
        liberar_evento(&lista_eventos->eventos[i]);
    }
    free(lista_eventos->eventos);
    lista_eventos->eventos = NULL;
    lista_eventos->cantidad_eventos = 0;
}
