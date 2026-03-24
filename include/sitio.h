#ifndef SITIO_H
#define SITIO_H

typedef struct {
    char *nombre;
    char *ubicacion;
    char *sitio_web;
} Sitio;

Sitio crear_sitio(const char *nombre, const char* ubicacion, const char *sitio_web);
void liberar_sitio(Sitio *sitio);
#endif //SITIO_H