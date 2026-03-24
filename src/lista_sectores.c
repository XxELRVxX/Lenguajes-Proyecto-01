#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_sectores.h"

ListaSectores crear_lista_sectores() {
    ListaSectores lista;
    lista.cantidad_sectores = 0;
    lista.sectores = NULL;
    return lista;
}

int agregar_sector(ListaSectores *lista, Sector *nuevo_sector) {
    if (buscar_sector(lista, nuevo_sector->nombre) != NULL) {
        liberar_sector(nuevo_sector);
        return OPERACION_FALLIDA_DUPLICADO;
    }

    Sector *temp = realloc(lista->sectores, (lista->cantidad_sectores + 1) * sizeof(Sector));
    if (temp == NULL) {
        liberar_sector(nuevo_sector);
        return OPERACION_FALLIDA_MEMORIA;
    }

    lista->sectores = temp;
    lista->sectores[lista->cantidad_sectores] = *nuevo_sector;
    lista->cantidad_sectores++;

    return OPERACION_EXITOSA;
}

void liberar_lista_sectores(ListaSectores *lista) {
    for (int i = 0; i < lista->cantidad_sectores; i++) {
        liberar_sector(&lista->sectores[i]);
    }
    free(lista->sectores);
    lista->sectores = NULL;
    lista->cantidad_sectores = 0;
}

Sector *buscar_sector(ListaSectores *lista, const char *nombre_sector) {
    for (int i = 0; i < lista->cantidad_sectores; i++) {
        if (strcmp(lista->sectores[i].nombre, nombre_sector) == 0) {
            return &lista->sectores[i];
        }
    }
    return NULL;
}

void mostrar_lista_sectores(const ListaSectores *lista) {
    for (int i = 0; i < lista->cantidad_sectores; i++) {
        mostrar_sector(&lista->sectores[i]);
    }
}

void resetear_lista_sectores(ListaSectores *lista) {
    for (int i = 0; i < lista->cantidad_sectores; i++) {
        resetear_sector(&lista->sectores[i]);
    }
}
