#ifndef SECTOR_H
#define SECTOR_H
#include "lista_asientos.h"

typedef struct {
    char *nombre;
    char inicial;
    int cantidad_asientos;
    ListaAsientos asientos;
}Sector;

Sector crear_sector(const char *nombre_sector, int cantidad, char inicial);
void liberar_sector(Sector *sector);
void resetear_sector(Sector *sector);
void mostrar_sector(const Sector *sector);


#endif //SECTOR_H