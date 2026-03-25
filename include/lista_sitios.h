#ifndef LISTA_SITIOS_H
#define LISTA_SITIOS_H

#include "sitio.h"

typedef struct {
    Sitio *sitios;
    int cantidad;
}ListaSitios;

ListaSitios crear_lista_sitios();
int agregar_sitio(ListaSitios *lista_sitios, Sitio *nuevo_sitio);
void liberar_lista_sitios(ListaSitios *lista_sitios);
Sitio *buscar_sitio(ListaSitios *lista_sitios, const char* nombre_sitio);
int cargar_sitios(ListaSitios *lista_sitios, const char *ruta_archivo);

#endif //LISTA_SITIOS_H