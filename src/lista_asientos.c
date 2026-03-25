#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_asientos.h"
#include "asiento.h"
#include "config.h"

ListaAsientos crear_lista_asientos(int cantidad, char inicial) {
    ListaAsientos lista_asientos;
    lista_asientos.cantidad_asientos = cantidad;
    lista_asientos.asientos = malloc(cantidad * sizeof(Asiento));

    for (int i = 0; i < cantidad; i++) {
        char numero_asiento[10];
        sprintf(numero_asiento,"%c%d", inicial, i+1);
        lista_asientos.asientos[i] = crear_asiento(numero_asiento);
    }
    return lista_asientos;
}

ListaAsientos crear_lista_asientos_vacia() {
    ListaAsientos lista;
    lista.asientos = NULL;
    lista.cantidad_asientos = 0;
    return lista;
}

int agregar_asiento_a_lista(ListaAsientos *lista_asientos, Asiento *asiento) {
    if (buscar_asiento(lista_asientos, asiento->numero_asiento) != NULL) {
        liberar_asiento(asiento);
        return OPERACION_FALLIDA_DUPLICADO;
    }

    Asiento *temp_lista_asientos = realloc(lista_asientos->asientos, (lista_asientos->cantidad_asientos + 1) * sizeof(Asiento));
    if (temp_lista_asientos == NULL) {
        liberar_asiento(asiento);
        return OPERACION_FALLIDA_MEMORIA;
    }
    lista_asientos->asientos = temp_lista_asientos;
    lista_asientos->asientos[lista_asientos->cantidad_asientos] = *asiento;
    lista_asientos->cantidad_asientos++;
    return OPERACION_EXITOSA;
}

void liberar_lista_asientos(ListaAsientos *lista_asientos) {
    for (int i = 0; i < lista_asientos->cantidad_asientos; i++) {
        liberar_asiento(&lista_asientos->asientos[i]);
    }
    free(lista_asientos->asientos);
    lista_asientos->asientos = NULL;

}

void resetear_lista_asientos(ListaAsientos *lista_asientos) {
    for (int i = 0; i<lista_asientos->cantidad_asientos; i++) {
        desocupar_asiento(&lista_asientos->asientos[i]);
    }
}

void mostrar_lista_asientos(const ListaAsientos *lista_asientos) {
    for (int i = 0; i < lista_asientos->cantidad_asientos; i++) {
        informacion_asiento(&lista_asientos->asientos[i]);
    }
}

Asiento *buscar_asiento(ListaAsientos *lista_asientos, const char *numero_asiento) {
    for (int i = 0; i<lista_asientos->cantidad_asientos; i ++) {
        if (strcmp(lista_asientos->asientos[i].numero_asiento,numero_asiento) == 0) {
            return &lista_asientos->asientos[i];
        }
    }
    return NULL; 
}

Asiento *obtener_asiento(ListaAsientos *lista_asientos, int indice) {
    if (!lista_asientos || indice < 0 || indice >= lista_asientos->cantidad_asientos) {
        return NULL;
    } else {
        return &lista_asientos->asientos[indice];
    }
}

int contar_asientos_disponibles(const ListaAsientos *lista_asientos) {
    int disponibles = 0;

    for (int i = 0; i < lista_asientos->cantidad_asientos; i++) {
        if (lista_asientos->asientos[i].estado == ASIENTO_DISPONIBLE) {
            disponibles++;
        }
    }
    return disponibles;
}