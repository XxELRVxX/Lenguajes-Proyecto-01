#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sector.h"

Sector crear_sector(const char *nombre_sector, int cantidad_asientos, char inicial) {
    Sector sector;
    sector.nombre = malloc(strlen(nombre_sector) + 1);
    strcpy(sector.nombre,nombre_sector);
    sector.inicial = inicial;
    sector.cantidad_asientos = cantidad_asientos;
    sector.asientos = crear_lista_asientos(cantidad_asientos,inicial);

    return sector;
}

void liberar_sector(Sector *sector) {
    if (sector->nombre) {
        free(sector->nombre);
        sector->nombre = NULL;
    }
    liberar_lista_asientos(&sector->asientos);
    sector->cantidad_asientos = 0;
    sector->inicial = '\0';
}

void resetear_sector(Sector *sector) {
    resetear_lista_asientos(&sector->asientos);
}

void mostrar_sector(const Sector *sector) {
    printf("Sector: %s | Inicial: %c | Cantidad de asientos: %d\n",
    sector->nombre, sector->inicial, sector->cantidad_asientos);
    mostrar_lista_asientos(&sector->asientos);    
}