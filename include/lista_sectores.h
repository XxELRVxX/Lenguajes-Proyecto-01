#ifndef LISTA_SECTORES_H
#define LISTA_SECTORES_H

#include "sector.h"
#include "config.h"  

typedef struct {
    int cantidad_sectores;
    Sector *sectores; 
} ListaSectores;

ListaSectores crear_lista_sectores();
int agregar_sector(ListaSectores *lista, Sector *nuevo_sector);
void liberar_lista_sectores(ListaSectores *lista);
Sector *buscar_sector(ListaSectores *lista, const char *nombre_sector);
void mostrar_lista_sectores(const ListaSectores *lista);
void resetear_lista_sectores(ListaSectores *lista);

#endif
