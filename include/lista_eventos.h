#ifndef LISTA_EVENTOS_H
#define LISTA_EVENTOS_H

#include "evento.h"

typedef struct {
    Evento *eventos;
    int cantidad_eventos;
}ListaEventos;


ListaEventos crear_lista_eventos();
int agregar_evento(ListaEventos *lista_eventos, Evento *nuevo_evento);
Evento *buscar_evento(ListaEventos *lista_eventos, const char *nombre_evento);
void mostrar_lista_eventos(const ListaEventos *lista_eventos);
void liberar_lista_eventos(ListaEventos *lista_eventos);

#endif //LISTA_EVENTOS_H