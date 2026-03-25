#ifndef SITIO_H
#define SITIO_H
#include "lista_sectores.h"

typedef struct {
    char *nombre;
    char *ubicacion;
    char *sitio_web;
    ListaSectores lista_sectores;
} Sitio;

Sitio crear_sitio(const char *nombre, const char* ubicacion, const char *sitio_web);
void liberar_sitio(Sitio *sitio);
void mostrar_sitio(const Sitio *sitio);
int contar_asientos_sitio(const Sitio *sitio);

#endif //SITIO_H