#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sitio.h"
#include "config.h"

Sitio crear_sitio(const char *nombre, const char *ubicacion, const char *sitio_web) {
    Sitio sitio;

    sitio.nombre = malloc(strlen(nombre) + 1);
    strcpy(sitio.nombre, nombre);

    sitio.ubicacion = malloc(strlen(ubicacion) + 1);
    strcpy(sitio.ubicacion,ubicacion);

    if (sitio_web != NULL) {
        sitio.sitio_web = malloc(strlen(sitio_web) + 1);
        strcpy(sitio.sitio_web, sitio_web);
    } else {
        sitio.sitio_web = NULL;
    }

    return sitio;  
}
void liberar_sitio(Sitio *sitio) {
    if (sitio->nombre) {
        free(sitio->nombre);
        sitio->nombre = NULL;
    }
    if (sitio->ubicacion) {
        free(sitio->ubicacion);
        sitio->ubicacion = NULL;
    }
    if (sitio->sitio_web) {
        free(sitio->sitio_web);
        sitio->sitio_web = NULL;
    }
}