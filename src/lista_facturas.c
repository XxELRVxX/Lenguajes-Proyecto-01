/**
 * @file lista_facturas.c
 * @brief Implementacion de las funciones para el manejo de listas de facturas.
 */

#include "lista_facturas.h"

/**
 * @brief Crea una lista de facturas vacia.
 * @return ListaFacturas vacia.
 */
ListaFacturas crear_lista_facturas() {
    ListaFacturas lista;
    lista.facturas = NULL;
    lista.cantidad_facturas = 0;
    return lista;
}

/**
 * @brief Agrega una factura a la lista.
 * @param lista_facturas Puntero a la lista de facturas.
 * @param factura Puntero a la factura a agregar.
 * @return Codigo de exito o error.
 */
int agregar_factura(ListaFacturas *lista_facturas, Factura *factura) {
    if (buscar_factura(lista_facturas, factura->id) != NULL) {
        liberar_factura(factura);
        return OPERACION_FALLIDA_DUPLICADO;
    }

    Factura *temp = realloc(lista_facturas->facturas, (lista_facturas->cantidad_facturas + 1) * sizeof(Factura));
    if (temp == NULL) {
        liberar_factura(factura);
        return OPERACION_FALLIDA_MEMORIA;
    }
    lista_facturas->facturas = temp;
    lista_facturas->facturas[lista_facturas->cantidad_facturas] = *factura;
    lista_facturas->cantidad_facturas++;
    return OPERACION_EXITOSA;
}

Factura *buscar_factura(const ListaFacturas *lista, int id) {
    for (int i = 0; i < lista->cantidad_facturas; i++) {
        if (lista->facturas[i].id == id) {
            return &lista->facturas[i];
        }
    }
    return NULL;
}

/**
 * @brief Muestra la informacion de todas las facturas de la lista.
 * @param lista_facturas Puntero constante a la lista de facturas.
 */
void mostrar_lista_facturas(const ListaFacturas *lista_facturas) {
    if (lista_facturas->cantidad_facturas == 0) {
        printf("No hay facturas registradas.\n");
        return;
    }
    printf("Lista de facturas (%d):\n", lista_facturas->cantidad_facturas);
    for (int i = 0; i < lista_facturas->cantidad_facturas; i++) {
        Factura *f = &lista_facturas->facturas[i];
        printf("Factura #%d | Evento: %s | Fecha: %02d/%02d/%04d | Cliente: %s | Subtotal: %.2f\n",
               f->id, f->evento->nombre_evento,
               f->fecha_compra.dia, f->fecha_compra.mes, f->fecha_compra.anio,
               f->cliente_nombre, f->subtotal);
    }
}

/**
 * @brief Libera la memoria de la lista de facturas.
 * @param lista_facturas Puntero a la lista de facturas a liberar.
 */
void liberar_lista_facturas(ListaFacturas *lista_facturas) {
    for (int i = 0; i < lista_facturas->cantidad_facturas; i++) {
        liberar_factura(&lista_facturas->facturas[i]);
    }
    free(lista_facturas->facturas);
    lista_facturas->facturas = NULL;
    lista_facturas->cantidad_facturas = 0;
}
