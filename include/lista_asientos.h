#ifndef LISTA_ASIENTOS_H
#define LISTA_ASIENTOS_H
#include "asiento.h"


typedef struct {
    int cantidad_asientos;
    Asiento *asientos;
}ListaAsientos;

ListaAsientos crear_lista_asientos(int cantidad, char inicial);
ListaAsientos crear_lista_asientos_vacia();
int agregar_asiento_a_lista(ListaAsientos *lista, Asiento *asiento);
void liberar_lista_asientos(ListaAsientos *lista_asientos);
void resetear_lista_asientos(ListaAsientos *lista_asientos);
void mostrar_lista_asientos(const ListaAsientos *lista_asientos);
Asiento *buscar_asiento(ListaAsientos *lista_asientos, const char *numero_asiento);
Asiento *obtener_asiento(ListaAsientos *lista_asientos, int indice);
int contar_asientos_disponibles(const ListaAsientos *lista_asientos);

#endif //LISTA_ASIENTOS_H