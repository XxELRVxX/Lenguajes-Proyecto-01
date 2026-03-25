#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_eventos.h"

ListaEventos crear_lista_eventos() {
    ListaEventos lista;
    lista.eventos = NULL;
    lista.cantidad_eventos = 0;
    return lista;
}

int agregar_evento(ListaEventos *lista_eventos, Evento *nuevo_evento) {
    Evento *temp_lista_eventos = realloc(lista_eventos->eventos, (lista_eventos->cantidad_eventos + 1) * sizeof(Evento)); 
    if (temp_lista_eventos == NULL) {
        return OPERACION_FALLIDA_MEMORIA;
    }
    lista_eventos->eventos = temp_lista_eventos;
    lista_eventos->eventos[lista_eventos->cantidad_eventos] = *nuevo_evento;
    lista_eventos->cantidad_eventos++;
    return OPERACION_EXITOSA;
}

Evento *buscar_evento(ListaEventos *lista_eventos, const char *nombre_evento) {
    for (int i = 0; i<lista_eventos->cantidad_eventos; i++) {
        if (strcmp(lista_eventos->eventos[i].nombre_evento, nombre_evento) == 0) {
            return &lista_eventos->eventos[i];
        }
    }
    return NULL;
}

void mostrar_lista_eventos(const ListaEventos *lista) {
    printf("Lista de eventos:\n");
    for (int i = 0; i < lista->cantidad_eventos; i++) {
        mostrar_evento(&lista->eventos[i]);
    }
}

void liberar_lista_eventos(ListaEventos *lista_eventos) {
    for (int i = 0; i<lista_eventos->cantidad_eventos; i++) {
        liberar_evento(&lista_eventos->eventos[i]);
    }
    free(lista_eventos->eventos);
    lista_eventos->eventos = NULL;
    lista_eventos->cantidad_eventos = 0;
}
