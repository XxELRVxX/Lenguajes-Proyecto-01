#ifndef LISTA_FACTURAS_H
#define LISTA_FACTURAS_H

#include "factura.h"

typedef struct {
    Factura *facturas;
    int cantidad_facturas;
} ListaFacturas;

ListaFacturas crear_lista_facturas();
Factura *buscar_factura(const ListaFacturas *lista, int id);
int agregar_factura(ListaFacturas *lista_facturas, Factura *factura);
void mostrar_lista_facturas(const ListaFacturas *lista_facturas);
void liberar_lista_facturas(ListaFacturas *lista_facturas);

#endif // LISTA_FACTURAS_H
